#ifndef _INIT_H
#define _INIT_H
#include "LPC11xx.h"

extern int result;          //�¶Ƚ��
extern int flag;            //�ֶ��Զ���־ 0Ϊ�Զ� 1Ϊ�ֶ�
extern int trans;           // 0Ϊ���϶� 1Ϊ���϶�
extern void SYSINIT(void);   //ϵͳ��ʼ��
extern void Delay(void);   //ϵͳ������ʱ
extern void mode(void);			//�ֶ��Զ�ģʽ�л�
extern void resultmode(void);  //�����Զ�ɢ��
extern void translation(void);   //�������ʾ�¶� ��ת��
extern void INT3(void);  //�ж�3��ʼ��
extern void PIOINT3_IRQHandler(void); //�ж�3������
extern void MYGPIOINIT(void);     //�ܽ�GPIO2.0��ʼ��
extern void KEYInit(void);        //�ܽ�GPIO3.4������ʼ��

#endif
