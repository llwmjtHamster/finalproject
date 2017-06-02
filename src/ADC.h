#ifndef __ADC_H__
#define __ADC_H__
#include "LPC11xx.h"

extern void DelayADC(uint32_t ulTime); //软件延时
extern void ADC_Init(void);    //ADC初始化
extern int ADCData(void);      //取温度值

#endif