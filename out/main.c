#include <string.h>
#include "LPC11xx.h"
#include "INIT.h"     //系统初始化及中断,配置GPIO
#include "UART.h"    //串口通信
#include "ADC.h"    //ADC 温度传感器
#include "Digital.h"//数码管显示
/********************************************************************************
* FunctionName   : main()
* Description    : 主程序 可以显示当前温度 超过温度自动散热 切换手动和自动模式 
*                          判断串口关键字并返回温度
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
int main(void)
{
	float result;
	SYSINIT();
	while(1)
	{
		result=ADCData(); //当前温度
		resultmode();   //超过18摄氏度自动旋转风扇否则不旋转
		Judge();        //判断是否输入0xff
		translation();    //数码管显示温度  带转换
	}
}
