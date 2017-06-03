#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "LPC11xx.h"

extern void DelayDisplay(void);          //延时函数
extern void GPIOInit(void);           //P2.0~P2.11管脚初始化
extern void Display(uint32_t value);   //显示函数

#endif