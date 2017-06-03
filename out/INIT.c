#include <stdio.h>
#include <string.h>
#include "INIT.h"      //系统初始化和中断，配置GPIO
#include "UART.h"     //串口通信
#include "ADC.h"     //ADC 温度传感器
#include "Display.h"

int result;            //定义当前温度
int flag=0;            //手动自动标志 0为自动 1为手动
int rotate=0;          //当前风扇旋转状态
int trans=0;           // 0为摄氏度 1为华氏度

/********************************************************************************
* FunctionName   : SYSINIT()
* Description    : 系统初始化
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void SYSINIT(void)
{
	ADC_Init();
	UART_Init();
	INT3();
	GPIOINIT();
	NVIC_EnableIRQ(EINT3_IRQn);
}

/********************************************************************************
* FunctionName   : Delay()
* Description    : 延时函数
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void Delay()
{
		uint16_t i,j;
		for (i=0;i<2000;i++)
			for (j=0;j<200;j++);
}

/********************************************************************************
* FunctionName   : mode()
* Description    : 切换手动 自动模式
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void mode(void)     //配置系统设备，串行端口
{
	if(flag == 0)   //档位/0:自动 1:手动
	{
				if(rotate == 0)  //风扇状态 0:风扇不转 1:风扇转动
				{
				 LPC_GPIO1->DATA  = ~(LPC_GPIO1->DATA);	
					rotate=1;
				}
				
	}
	if(flag == 1)  //手动挡/程序判定风扇旋转   取反，让不旋转  
	{
				if(rotate == 1)
				{
					LPC_GPIO1->DATA  &= ~(1<<2);	
						rotate=0;
				}
				
	}
	if(flag == 1)  //手动挡/风扇不旋转   让风扇旋转
	{
				if(rotate == 0)
				{
				 LPC_GPIO1->DATA  |= (1<<2) ;	
					rotate=1;
				}
				
	}
}

/********************************************************************************
* FunctionName   : resultmode()
* Description    : 高温自动散热
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void resultmode(void)
{
	if(flag == 0 )
	{
		if(result > 29)
		{
			LPC_GPIO1->DATA |= (1<<2);
			rotate = 1;   //标志风扇旋转
		}
		else
		{
			LPC_GPIO1->DATA &= ~(1<<2);
			rotate = 0;  //标志风扇不旋转
		}
	}
}

/********************************************************************************
* FunctionName   : translation(void)
* Description    : 数码管显示温度 带转换
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void translation(void)
{
	if(trans == 0)
		{
			Display(result);   //数码管显示摄氏度
		}
		if(trans == 1)
		{
			result=(int)(result*1.8+32);
			Display(result);   //数码管显示华氏度
		}
}
void INT3()
{	
			LPC_GPIO3->IE |= (1<<0);			   //使能中断
			LPC_GPIO3->IS &= ~(1<<0);			   //边沿触发模式
			LPC_GPIO3->IEV &= ~(1<<0);			 //下降沿触发
	
			LPC_GPIO3->IE |= (1<<3);			   //使能中断
			LPC_GPIO3->IS &= ~(1<<3);			   //边沿触发模式
			LPC_GPIO3->IEV &= ~(1<<3);			 //下降沿触发
}

/********************************************************************************
* FunctionName   : PIOINT3_IRQHandler()
* Description    : 中断3切换任务
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void PIOINT3_IRQHandler()
{
		Delay();           //按键消抖
		if((LPC_GPIO3->MIS & (1<<3)) == (1<<3))   //判断当前是否产生中断
		{
			mode();   //切换自动手动模式 
			flag = ~flag;                          // 手动自动标志位切换
			LPC_GPIO3->IC = (1<<3);                  //消除中断标志
		}
		
		if((LPC_GPIO3->MIS & (1<<0)) == (1<<0))   //判断当前是否产生中断
		{
			if(trans == 0)
			{
				trans=1;
			}
			else
			{
				trans=0;
			}
			LPC_GPIO3->IC = (1<<0);                  //消除中断标志
		}
}
void GPIOINIT(void)
{
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);
		LPC_IOCON->R_PIO1_2  &= ~0x07;
    LPC_IOCON->R_PIO1_2  |= 0x01;
	  LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16);
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);
		LPC_GPIO1->DIR  |= (1<<2);
		LPC_GPIO1->DATA  &= ~(1<<2);
}

/********************************************************************************
* FunctionName   : KEYInit()
* Description    : 按键初始化 GPIO3.3 GPIO3.0
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void KEYInit()
{
	    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
			LPC_IOCON->PIO3_3 &= ~0x07;    
			LPC_IOCON->PIO3_3  |= 0x00;
			LPC_IOCON->PIO3_0 &= ~0x07;    
			LPC_IOCON->PIO3_0  |= 0x00;
			LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);
	
			LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
			LPC_GPIO3->DIR |= (1<<3);
			LPC_GPIO3->DATA &= ~(1<<3);
			LPC_GPIO3->DIR |= (1<<0);
			LPC_GPIO3->DATA &= ~(1<<0);
	
}


