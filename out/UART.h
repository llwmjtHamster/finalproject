#ifndef _UART_H
#define _UART_H

#include "LPC11xx.h"
#define UART_BPS 115200               //设置波特率为115200

extern int temp;
extern void UART_Init (void);        //串口初始化，设置为8位数据位，1为停止位，无奇偶校验，波特率为115200
extern void UART_SendByte (uint8_t ucDat);  //查询法发送数据
extern uint8_t UART_GetByte(void);          //查询法接收数据
extern void Judge(void);                    //判断输入
extern void UART_SendStr(char *pucStr);


#endif