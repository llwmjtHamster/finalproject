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
    LPC_IOCON->R_PIO1_0 &= ~0xBF; //PIO1_0为模拟输入模式
    LPC_IOCON->R_PIO1_0 |=  0x02; //PIO1_0模拟输入通道1
    LPC_SYSCON->PDRUNCFG &= ~(0x01 << 4); //ADC模块上电
    LPC_SYSCON->SYSAHBCLKCTRL |=  (0x01 << 13); //使能ADC模块时钟 
    LPC_ADC->CR = ( 0x02 << 0 ) |  //SEL=1,选择ADC1
                  ((SystemCoreClock / 1000000 - 1) << 8 ) | //转换时钟1MHz 
                  ( 0 << 16 ) | //软件控制转换操作
                  ( 0 << 17 ) | //使能11clocks转换
                  ( 0 << 24 ) | //ADC转换停止 
                  ( 0 << 27 );  //直接启动ADC转换,此位无效
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
				LPC_ADC->CR |= (1 << 24);	//立即转换               
				while((LPC_ADC->DR[1] & 0x80000000) == 0);	//读取DR0的Done        
				LPC_ADC->CR |= (1 <<24);	// 第一次转换结果丢弃     
				while((LPC_ADC->DR[1] & 0x80000000) == 0);	//读取DR0的Done        
				ulADCBuf = LPC_ADC->DR[1];	//读取结果寄存器         
				ulADCBuf = (ulADCBuf >> 6) & 0x3ff;	//数据位从第6位开始存储，占据10位                       
				ulADCData += ulADCBuf;	//数据累加			
			}
			ulADCData = ulADCData / 10;	//采样10次进行滤波处理    
			ulADCData = (ulADCData * 3300) / 1024;	//数字量转换为模拟量
			
			Rt=((ulADCData*10000)/(3300-ulADCData));  //计算温敏电阻值
			for(i=0;i<75;i++)                         //通过电阻值匹配温度表
			{
				if(Rt >= temp[i])
				{
					result=i;
					break;
				}
			}
			return result;
}
