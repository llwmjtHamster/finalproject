//#include "Digital.h"
//#include "LPC11xx.h"
//#include "INIT.h"

//uint8_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

///*****************************************************
//*FunctionName      :DelayDigital()                 
//*Description       :��ʱ����
//*EntryParameter    :None
//*ReturnValue       :None
//*****************************************************/

//void DelayDigital()
//{
//	uint16_t i = 4000;
//	while(i--);
//}

///*****************************************************
//*FunctionName      :GPIOInit()                 
//*Description       :�����IO�ڳ�ʼ��������ռ��P2.0~P2.11
//*EntryParameter    :None
//*ReturnValue       :None
//*****************************************************/

//void GPIOInit(void)
//{
//	LPC_SYSCON->SYSAHBCLKCTRL  |= (1<<6);
//	LPC_GPIO2 ->DIR |= 0xFFF;               //����P2.0~P2.11Ϊ���
//}

///*****************************************************
//*FunctionName      :Dislay()                 
//*Description       :��ʾ����
//*EntryParameter    :value: ����ʾ����
//*ReturnValue       :None
//*****************************************************/

//void Dislay(uint32_t value)
//{
//	LPC_GPIO2->DATA &= ~(1<<8);
//	LPC_GPIO2->DATA	= 0xe00 + table[value/1000];	
//	DelayDigital();
//	LPC_GPIO2->DATA |= (1<<8);
//	LPC_GPIO2->DATA = 0xfff;
//	
//	LPC_GPIO2->DATA &= ~(1<<9);
//	LPC_GPIO2->DATA	= 0xd00 + table[value%1000/100];	
//	DelayDigital();
//	LPC_GPIO2->DATA |= (1<<9);
//	LPC_GPIO2->DATA = 0xfff;
//	
//	LPC_GPIO2->DATA &= ~(1<<10);
//	LPC_GPIO2->DATA = 0xb00 + table[value%1000%100/10];	
//	DelayDigital();
//	LPC_GPIO2->DATA |= (1<<10);
//	LPC_GPIO2->DATA = 0xfff;
//	
//  LPC_GPIO2->DATA &= ~(1<<11);
//	LPC_GPIO2->DATA = 0x700 +  table[value%1000%1000%10];	
//	DelayDigital();
//	LPC_GPIO2->DATA |= (1<<11);
//	LPC_GPIO2->DATA = 0xfff;   

//}
