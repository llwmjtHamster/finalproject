#ifndef __ADC_H__
#define __ADC_H__
#include "LPC11xx.h"

extern void DelayADC(uint32_t ulTime); //�����ʱ
extern void ADC_Init(void);    //ADC��ʼ��
extern int ADCData(void);      //ȡ�¶�ֵ

#endif