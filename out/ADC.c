#include "ADC.h"
#include <math.h>
#include "INIT.h"

int temp[75]={23393,22364,21385,20452,19564,18719,
							17915,17149,16421,15727,15067,14438,13840,13270,12728,12212,11720,
							11252,10806,10381,9976,9590,9223,8872,8538,8220,7916,7626,7350,
							7086,6835,6595,6366,6148,5940,5742,5553,5373,5202,5039,4884,4737,
							4598,4466,4342,4224,4113,4010,3913,3822,3739,3661,3591,3527,3469,
							3418,3373,3335,3303,3278,3260,3249,3244,3246,3256,3272,3296,3326,
							3365,3411,3464,3525,3595,3672,3757};

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
    LPC_IOCON->R_PIO1_0 &= ~0xBF; //PIO1_0Ϊģ������ģʽ
    LPC_IOCON->R_PIO1_0 |=  0x02; //PIO1_0ģ������ͨ��1
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << 4); //ADCģ���ϵ�
    LPC_SYSCON->SYSAHBCLKCTRL |=  (0x01 << 13); //ʹ��ADCģ��ʱ�� 
    LPC_ADC->CR = ( 0x02 << 0 ) |  //SEL=1,ѡ��ADC1
                  ((SystemCoreClock / 1000000 - 1) << 8 ) | //ת��ʱ��1MHz 
                  ( 0 << 16 ) | //�������ת������
                  ( 0 << 17 ) | //ʹ��11clocksת��
                  ( 0 << 24 ) | //ADCת��ֹͣ 
                  ( 0 << 27 );  //ֱ������ADCת��,��λ��Ч
}

int ADCData(void)
{
			uint32_t  i;
			int Rt=0;
	    uint32_t  ulADCData; 
			uint32_t  ulADCBuf;
			ulADCData = 0;                                                            
			for (i = 0; i < 10; i++)                                                  
			{                                                                 
				LPC_ADC->CR |= (1 << 24);	//����ת��               
				while((LPC_ADC->DR[1] & 0x80000000) == 0);	//��ȡDR0��Done        
				LPC_ADC->CR |= (1 <<24);	// ��һ��ת���������     
				while((LPC_ADC->DR[1] & 0x80000000) == 0);	//��ȡDR0��Done        
				ulADCBuf = LPC_ADC->DR[1];	//��ȡ����Ĵ���         
				ulADCBuf = (ulADCBuf >> 6) & 0x3ff;	//����λ�ӵ�6λ��ʼ�洢��ռ��10λ                       
				ulADCData += ulADCBuf;	//�����ۼ�			
			}
			ulADCData = ulADCData / 10;	//����10�ν����˲�����    
			ulADCData = (ulADCData * 3300) / 1024;	//������ת��Ϊģ����
			
			Rt=((ulADCData*10000)/(3300-ulADCData));  //������������ֵ
			for(i=0;i<75;i++)                         //ͨ������ֵƥ���¶ȱ�
			{
				if(Rt >= temp[i])
				{
					result=i;
					break;
				}
			}
			return result;
}
