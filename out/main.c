#include <string.h>
#include "LPC11xx.h"
#include "INIT.h"     //系统初始化及中断,配置GPIO
#include "UART.h"    //串口通信
#include "ADC.h"    //ADC 温度传感器
//#include "Digital.h"//数码管显示
#include "oleddelay.h"
#include "oled.h"

unsigned char tx_buf[]={"0123456789"};
unsigned char rx_buf[32];

/********************************************************************************
* FunctionName   : main()
* Description    : 主程序 可以显示当前温度 超过温度自动散热 切换手动和自动模式 
*                          判断串口关键字并返回温度
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
int main(void)
{
	int t=0;
	SYSINIT();
	OLED_Init();    //OLED初始化
	OLED_Clear();
	delay_ms(10);   //清屏等待
    OLED_ShowString(0,0,"LPC");    //显示字符串"LPC"	
    OLED_ShowString(0,2,"Temperature :");       //显示字符串"Temperature :"
  	OLED_Clear();
    OLED_ShowString(0,6,"Author :126");        //显示字符串"Author :"
	while(1)
	{
		result=ADCData(); //当前温度
		resultmode();   //超过18摄氏度自动旋转风扇否则不旋转
		Judge();        //判断是否输入0xff
		translation();    //显示温度  带转换
		t++;
//		OLED_ShowNum(0,4,t,5,16);   //显示数字变量
		if(t>=20000)t=0;
		delay_ms(500);          //延时500ms
	}
}
