#include "oleddelay.h"
#include "LPC11xx.h"
int ticks = 0;
void delay_ms(int ms)       //延时到毫秒
{
    SysTick->CTRL &= ~(1 << 2);         //CLKSOURCE = 0 ， 设置为参考时钟，即系统时钟一半
    SysTick->LOAD = SystemCoreClock/2/1000*ms-1;            //设置重装载值为SystemCoreClock/2/1000*ms-1
    SysTick->VAL = 0;           //将当前值清零
    SysTick->CTRL = ((1<<1) | (1<<0));          //使能中断，启动系统节拍定时器
    while(!ticks);              //等待定时时间到，ticks = 1
    ticks = 0;              //清零
    SysTick->CTRL = 0;          //停止系统节拍定时器
}


void delay_us(int us)       //延时到微秒
{
    SysTick->CTRL &= ~(1 << 2);         //CLKSOURCE = 0 ， 设置为参考时钟，即系统时钟一半
    SysTick->LOAD = SystemCoreClock/2/1*us-1;            //设置重装载值为SystemCoreClock/2/1*us-1
    SysTick->VAL = 0;           //将当前值清零
    SysTick->CTRL = ((1<<1) | (1<<0));          //使能中断，启动系统节拍定时器
    while(!ticks);              //等待定时时间到，ticks = 1
    ticks = 0;              //清零
    SysTick->CTRL = 0;          //停止系统节拍定时器
}

void SysTick_Handler(void)          //系统节拍定时器中断服务函数（此函数在startup_LPC11xx.s中可找到）
{
    ticks++;        //加1表示定时器时间到了
}