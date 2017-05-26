#ifndef _UART_H
#define _UART_H

#include "LPC11xx.h"
#define UART_BPS 115200               //���ò�����Ϊ115200

extern int temp;
extern void UART_Init (void);        //���ڳ�ʼ��������Ϊ8λ����λ��1Ϊֹͣλ������żУ�飬������Ϊ115200
extern void UART_SendByte (uint8_t ucDat);  //��ѯ����������
extern uint8_t UART_GetByte(void);          //��ѯ����������
extern void Judge(void);                    //�ж�����
extern void UART_SendStr(char *pucStr);


#endif