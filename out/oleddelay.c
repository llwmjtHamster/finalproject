#include "oleddelay.h"
#include "LPC11xx.h"
int ticks = 0;
void delay_ms(int ms)       //��ʱ������
{
    SysTick->CTRL &= ~(1 << 2);         //CLKSOURCE = 0 �� ����Ϊ�ο�ʱ�ӣ���ϵͳʱ��һ��
    SysTick->LOAD = SystemCoreClock/2/1000*ms-1;            //������װ��ֵΪSystemCoreClock/2/1000*ms-1
    SysTick->VAL = 0;           //����ǰֵ����
    SysTick->CTRL = ((1<<1) | (1<<0));          //ʹ���жϣ�����ϵͳ���Ķ�ʱ��
    while(!ticks);              //�ȴ���ʱʱ�䵽��ticks = 1
    ticks = 0;              //����
    SysTick->CTRL = 0;          //ֹͣϵͳ���Ķ�ʱ��
}


void delay_us(int us)       //��ʱ��΢��
{
    SysTick->CTRL &= ~(1 << 2);         //CLKSOURCE = 0 �� ����Ϊ�ο�ʱ�ӣ���ϵͳʱ��һ��
    SysTick->LOAD = SystemCoreClock/2/1*us-1;            //������װ��ֵΪSystemCoreClock/2/1*us-1
    SysTick->VAL = 0;           //����ǰֵ����
    SysTick->CTRL = ((1<<1) | (1<<0));          //ʹ���жϣ�����ϵͳ���Ķ�ʱ��
    while(!ticks);              //�ȴ���ʱʱ�䵽��ticks = 1
    ticks = 0;              //����
    SysTick->CTRL = 0;          //ֹͣϵͳ���Ķ�ʱ��
}

void SysTick_Handler(void)          //ϵͳ���Ķ�ʱ���жϷ��������˺�����startup_LPC11xx.s�п��ҵ���
{
    ticks++;        //��1��ʾ��ʱ��ʱ�䵽��
}