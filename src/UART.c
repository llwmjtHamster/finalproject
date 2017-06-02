#include "UART.h"
#include "INIT.h"
#include <stdio.h>

char GcRcvBuf[20];

/********************************************************************************
* FunctionName   : UART_Init()
* Description    : 串口初始化，设置为8位数据位，1为停止位，无奇偶校验，波特率为115200
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void UART_Init(void)
{
    uint16_t usFdiv;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16); //打开IOCON配置时钟
    LPC_IOCON->PIO1_6  &= ~0x07;
    LPC_IOCON->PIO1_6  |= (1<<0); //配置P1.6为RXD 
    LPC_IOCON->PIO1_7  &= ~0x07;
    LPC_IOCON->PIO1_7  |= (1<<0); //配置P1.7为TXD 
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12); //打开UART功能部件时钟 
    LPC_SYSCON->UARTCLKDIV = 0x01;  //UART时钟分频 
    
    LPC_UART->LCR  = 0x83; // 允许设置波特率  
    usFdiv = (SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS; //设置波特率
    LPC_UART->DLM  = usFdiv / 256;
    LPC_UART->DLL  = usFdiv % 256; 
    LPC_UART->LCR  = 0x03; // 锁定波特率 
    LPC_UART->FCR  = 0x07;
}

/********************************************************************************
* FunctionName   : UART_SendByte()
* Description    : 向串口发送字节数据。并等待数据发送完成，使用查询方式
* EntryParameter : ucDat:要发送的数据
* ReturnValue    : None
********************************************************************************/

void UART_SendByte(uint8_t ucDat)
{
    LPC_UART->THR = ucDat; //写入数据
    while ((LPC_UART->LSR & 0x40) == 0); //等待数据发送完毕
}

/********************************************************************************
* FunctionName   : UART_GetByte()
* Description    : 查询法接收数据
* EntryParameter : None
* ReturnValue    : 接收到的数据
********************************************************************************/

uint8_t UART_GetByte(void)
{
	uint8_t ucRcvData;
	while((LPC_UART->LSR & 0x01) == 0);
	ucRcvData = LPC_UART->RBR;
	return(ucRcvData);
}
/********************************************************************************
* FunctionName   : UART_SendStr()
* Description    : 向串口发送字符串
* EntryParameter : PucStr:要发送的字符串指针
* ReturnValue    : NONE
********************************************************************************/

void UART_SendStr(char *pucStr)
{
    while (1){
        if (*pucStr == '\0') break; 
        UART_SendByte (*pucStr++);
    }
}

/********************************************************************************
* FunctionName   : Judge()
* Description    : 判断输入是否是0xff
* EntryParameter : None
* ReturnValue    : NONE
********************************************************************************/

void Judge(void)
{
			if((LPC_UART->LSR & 0x01) == 1)
			{
					if(LPC_UART->RBR == 255)
					{
						if(trans == 0)
						{
						sprintf(GcRcvBuf," 温度 =%3d  \r\n",result);
						UART_SendStr(GcRcvBuf);
						}
						if(trans == 1)
						{
						sprintf(GcRcvBuf," 华氏度 =%3d  \r\n",(int)(result*1.8+32));
						UART_SendStr(GcRcvBuf);
						}
					}
					else
					{
						sprintf(GcRcvBuf," 错误  \r\n");
						UART_SendStr(GcRcvBuf);
					}
				
			}
}
