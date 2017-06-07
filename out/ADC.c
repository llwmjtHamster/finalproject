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
* Description    : 软件延时
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
* Description    : ADC初始化
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void ADC_Init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);
    LPC_IOCON->PIO1_11 &= ~0xBF; //PIO1_11为模拟输入模式
    LPC_IOCON->PIO1_11 |=  0x01; //PIO1_11模拟输入通道1
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << 4); //ADC模块上电
    LPC_SYSCON->SYSAHBCLKCTRL |=  (0x01 << 13); //使能ADC模块时钟 
    LPC_ADC->CR = ( 0x01 << 7 ) |  //SEL=1,选择ADC7
                  ((SystemCoreClock / 1000000 - 1) << 8 ) | //转换时钟1MHz 
                  ( 0 << 16 ) | //软件控制转换操作
                  ( 0 << 17 ) | //使能11clocks转换
                  ( 0 << 24 ) | //ADC转换停止 
                  ( 0 << 27 );  //直接启动ADC转换,此位无效
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
				LPC_ADC->CR |= (1 << 24);	//立即转换               
				while((LPC_ADC->DR[7] & 0x80000000) == 0);	//读取DR7的Done        
				LPC_ADC->CR |= (1 <<24);	// 第一次转换结果丢弃     
				while((LPC_ADC->DR[7] & 0x80000000) == 0);	//读取DR7的Done        
				ulADCBuf = LPC_ADC->DR[7];	//读取结果寄存器         
				ulADCBuf = (ulADCBuf >> 6) & 0x3ff;	//数据位从第6位开始存储，占据10位                       
				ulADCData += ulADCBuf;	//数据累加			
			}
			ulADCData = ulADCData / 10;	//采样10次进行滤波处理    
			ulADCData = (ulADCData * 3300) / 1024;	//数字量转换为模拟量
			
			Rt=((ulADCData*10000)/(3300-ulADCData));  //计算温敏电阻值
		
			for(i=0;i<100;i++)                         //通过电阻值匹配温度表
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
	