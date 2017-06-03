#ifndef _INIT_H
#define _INIT_H
#include "LPC11xx.h"

extern int result;          //温度结果
extern int flag;            //手动自动标志 0为自动 1为手动
extern int trans;           // 0为摄氏度 1为华氏度
extern void SYSINIT(void);   //系统初始化
extern void Delay(void);   //系统公用延时
extern void mode(void);			//手动自动模式切换
extern void resultmode(void);  //高温自动散热
extern void translation(void);   //数码管显示温度 带转换
extern void INT3(void);  //中断3初始化
extern void PIOINT3_IRQHandler(void); //中断3任务函数
extern void MYGPIOINIT(void);     //管脚GPIO2.0初始化
extern void KEYInit(void);        //管脚GPIO3.4按键初始化

#endif
