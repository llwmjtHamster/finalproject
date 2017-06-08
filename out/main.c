#include <string.h>
#include "LPC11xx.h"
#include "INIT.h"     //ϵͳ��ʼ�����ж�,����GPIO
#include "UART.h"    //����ͨ��
#include "ADC.h"    //ADC �¶ȴ�����
//#include "Digital.h"//�������ʾ
#include "oleddelay.h"
#include "oled.h"

unsigned char tx_buf[]={"0123456789"};
unsigned char rx_buf[32];

/********************************************************************************
* FunctionName   : main()
* Description    : ������ ������ʾ��ǰ�¶� �����¶��Զ�ɢ�� �л��ֶ����Զ�ģʽ 
*                          �жϴ��ڹؼ��ֲ������¶�
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
int main(void)
{
	int t=0;
	SYSINIT();
	OLED_Init();    //OLED��ʼ��
	OLED_Clear();
	delay_ms(10);   //�����ȴ�
    OLED_ShowString(0,0,"LPC");    //��ʾ�ַ���"LPC"	
    OLED_ShowString(0,2,"Temperature :");       //��ʾ�ַ���"Temperature :"
  	OLED_Clear();
    OLED_ShowString(0,6,"Author :126");        //��ʾ�ַ���"Author :"
	while(1)
	{
		result=ADCData(); //��ǰ�¶�
		resultmode();   //����18���϶��Զ���ת���ȷ�����ת
		Judge();        //�ж��Ƿ�����0xff
		translation();    //��ʾ�¶�  ��ת��
		t++;
//		OLED_ShowNum(0,4,t,5,16);   //��ʾ���ֱ���
		if(t>=20000)t=0;
		delay_ms(500);          //��ʱ500ms
	}
}
