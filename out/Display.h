#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "LPC11xx.h"

extern void DelayDisplay(void);          //��ʱ����
extern void GPIOInit(void);           //P2.0~P2.11�ܽų�ʼ��
extern void Display(uint32_t value);   //��ʾ����

#endif