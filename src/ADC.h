#ifndef __ADC_H__
#define __ADC_H__
#include "LPC11xx.h"

extern void DelayADC(uint32_t ulTime); //�����ʱ
extern void ADC_Init(void);    //ADC��ʼ��
extern float ADCData(void);      //ȡ�¶�ֵ
extern float CaculTwoPoint(float x1, float y1, float x2, float y2, float x);
extern float result;

#endif