#include <stdio.h>
#include <string.h>
#include "INIT.h"      //ϵͳ��ʼ�����жϣ�����GPIO
#include "UART.h"     //����ͨ��
#include "ADC.h"     //ADC �¶ȴ�����
#include "Display.h"

int result;            //���嵱ǰ�¶�
int flag=0;            //�ֶ��Զ���־ 0Ϊ�Զ� 1Ϊ�ֶ�
int rotate=0;          //��ǰ������ת״̬
int trans=0;           // 0Ϊ���϶� 1Ϊ���϶�

/********************************************************************************
* FunctionName   : SYSINIT()
* Description    : ϵͳ��ʼ��
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
* Description    : ��ʱ����
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
* Description    : �л��ֶ� �Զ�ģʽ
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void mode(void)     //����ϵͳ�豸�����ж˿�
{
	if(flag == 0)   //��λ/0:�Զ� 1:�ֶ�
	{
				if(rotate == 0)  //����״̬ 0:���Ȳ�ת 1:����ת��
				{
				 LPC_GPIO1->DATA  = ~(LPC_GPIO1->DATA);	
					rotate=1;
				}
				
	}
	if(flag == 1)  //�ֶ���/�����ж�������ת   ȡ�����ò���ת  
	{
				if(rotate == 1)
				{
					LPC_GPIO1->DATA  &= ~(1<<2);	
						rotate=0;
				}
				
	}
	if(flag == 1)  //�ֶ���/���Ȳ���ת   �÷�����ת
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
* Description    : �����Զ�ɢ��
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
			rotate = 1;   //��־������ת
		}
		else
		{
			LPC_GPIO1->DATA &= ~(1<<2);
			rotate = 0;  //��־���Ȳ���ת
		}
	}
}

/********************************************************************************
* FunctionName   : translation(void)
* Description    : �������ʾ�¶� ��ת��
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void translation(void)
{
	if(trans == 0)
		{
			Display(result);   //�������ʾ���϶�
		}
		if(trans == 1)
		{
			result=(int)(result*1.8+32);
			Display(result);   //�������ʾ���϶�
		}
}
void INT3()
{	
			LPC_GPIO3->IE |= (1<<0);			   //ʹ���ж�
			LPC_GPIO3->IS &= ~(1<<0);			   //���ش���ģʽ
			LPC_GPIO3->IEV &= ~(1<<0);			 //�½��ش���
	
			LPC_GPIO3->IE |= (1<<3);			   //ʹ���ж�
			LPC_GPIO3->IS &= ~(1<<3);			   //���ش���ģʽ
			LPC_GPIO3->IEV &= ~(1<<3);			 //�½��ش���
}

/********************************************************************************
* FunctionName   : PIOINT3_IRQHandler()
* Description    : �ж�3�л�����
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void PIOINT3_IRQHandler()
{
		Delay();           //��������
		if((LPC_GPIO3->MIS & (1<<3)) == (1<<3))   //�жϵ�ǰ�Ƿ�����ж�
		{
			mode();   //�л��Զ��ֶ�ģʽ 
			flag = ~flag;                          // �ֶ��Զ���־λ�л�
			LPC_GPIO3->IC = (1<<3);                  //�����жϱ�־
		}
		
		if((LPC_GPIO3->MIS & (1<<0)) == (1<<0))   //�жϵ�ǰ�Ƿ�����ж�
		{
			if(trans == 0)
			{
				trans=1;
			}
			else
			{
				trans=0;
			}
			LPC_GPIO3->IC = (1<<0);                  //�����жϱ�־
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
* Description    : ������ʼ�� GPIO3.3 GPIO3.0
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

