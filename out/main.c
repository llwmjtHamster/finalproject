#include <string.h>
#include "LPC11xx.h"
#include "INIT.h"     //ϵͳ��ʼ�����ж�,����GPIO
#include "UART.h"    //����ͨ��
#include "ADC.h"    //ADC �¶ȴ�����
#include "Display.h"//�������ʾ
/********************************************************************************
* FunctionName   : main()
* Description    : ������ ������ʾ��ǰ�¶� �����¶��Զ�ɢ�� �л��ֶ����Զ�ģʽ 
*                          �жϴ��ڹؼ��ֲ������¶�
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
int main(void)
{
	SYSINIT();
	while(1)
	{
		result=ADCData(); //��ǰ�¶�
		resultmode();   //����29���϶��Զ���ת���ȷ�����ת
		Judge();        //�ж��Ƿ�����0xff
		translation();    //�������ʾ�¶�  ��ת��
	}
}
