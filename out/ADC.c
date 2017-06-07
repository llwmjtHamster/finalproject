#include "ADC.h"
#include <math.h>
#include "INIT.h"

double temp[100]={33970,32220,30560,29010,27540,26510,24850,23610,22450,21350,20310,19330,18410,
                 17530,16700,15910,15170,14470,13800,13170,12570,12000,11460,10950,10460,10000,
                 9566,9154,8762,8389,8034,7697,7376,7070,6779,6502,6237,5986,5745,5516,5298,5089,
                 4890,4700,4518,4345,4179,4021,3869,3724,3586,3453,3326,3204,3088,2976,2869,2767,
                 2668,2574,2484,2397,2314,2234,2157,2083,2012,1944,1879,1816,1756,1698,1642,1588,
                 1537,1487,1439,1393,1349,1306,1265,1226,1187,1151,1115,1081,1048,1016,985.0,955.3,
                 926.6,899.0,872.3,846.6,821.8,797.9,774.8,752.5,730.9,710.1};


/********************************************************************************
* FunctionName   : DelayADC()
* Description    : �����ʱ
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void DelayADC(uint32_t ulTime) 
{
   uint32_t i;
   i = 0;
   while (ulTime--) 
	 {
		 for (i = 0; i < 5000; i++);
   }
	 
}

/********************************************************************************
* FunctionName   : ADC_Init()
* Description    : ADC��ʼ��
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void ADC_Init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);
    LPC_IOCON->PIO1_11 &= ~0xBF; //PIO1_11Ϊģ������ģʽ
    LPC_IOCON->PIO1_11 |=  0x01; //PIO1_11ģ������ͨ��1
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << 4); //ADCģ���ϵ�
    LPC_SYSCON->SYSAHBCLKCTRL |=  (0x01 << 13); //ʹ��ADCģ��ʱ�� 
    LPC_ADC->CR = ( 0x01 << 7 ) |  //SEL=1,ѡ��ADC7
                  ((SystemCoreClock / 1000000 - 1) << 8 ) | //ת��ʱ��1MHz 
                  ( 0 << 16 ) | //�������ת������
                  ( 0 << 17 ) | //ʹ��11clocksת��
                  ( 0 << 24 ) | //ADCת��ֹͣ 
                  ( 0 << 27 );  //ֱ������ADCת��,��λ��Ч
}

float ADCData(void)
{
			float result;
			uint32_t  i;
			uint32_t  Rt=0;
	    uint32_t  ulADCData; 
			uint32_t  ulADCBuf;
			ulADCData = 0;                                                            
			for (i = 0; i < 10; i++)                                                  
			{                                                                 
				LPC_ADC->CR |= (1 << 24);	//����ת��               
				while((LPC_ADC->DR[7] & 0x80000000) == 0);	//��ȡDR7��Done        
				LPC_ADC->CR |= (1 <<24);	// ��һ��ת���������     
				while((LPC_ADC->DR[7] & 0x80000000) == 0);	//��ȡDR7��Done        
				ulADCBuf = LPC_ADC->DR[7];	//��ȡ����Ĵ���         
				ulADCBuf = (ulADCBuf >> 6) & 0x3ff;	//����λ�ӵ�6λ��ʼ�洢��ռ��10λ                       
				ulADCData += ulADCBuf;	//�����ۼ�			
			}
			ulADCData = ulADCData / 10;	//����10�ν����˲�����    
			ulADCData = (ulADCData * 3300) / 1024;	//������ת��Ϊģ����
			
			Rt=((ulADCData*10000)/(3300-ulADCData));  //������������ֵ
		
			for(i=0;i<100;i++)                         //ͨ������ֵƥ���¶ȱ�
			{
				if(Rt <= temp[i] && Rt >= temp[i+1])
				{
					result=CaculTwoPoint(temp[i], i, temp[i+1], i+1, Rt);
					break;
				}
			}
			return result;
}
float CaculTwoPoint(float x1, float y1, float x2, float y2, float x)
{
    return result=y1 + ((y2 - y1) * (x - x1)) / (x2 - x1);
}
	