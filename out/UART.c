#include "LPC11xx.h"
#include <stdio.h>
#include "UART.h"
char GcRcvBuf[20];
int temp;
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
void UART_SendByte(uint8_t ucDat)
{
    LPC_UART->THR = ucDat; //写入数据
    while ((LPC_UART->LSR & 0x40) == 0); //等待数据发送完毕
}
uint8_t UART_GetByte(void)
{
	uint8_t ucRcvData;
	while((LPC_UART->LSR & 0x01) == 0);
	ucRcvData = LPC_UART->RBR;
	return(ucRcvData);
}
void UART_SendStr(char *pucStr)
{
    while (1){
        if (*pucStr == '\0') break; 
        UART_SendByte (*pucStr++);
    }
}
void Judge(void)
{
			if((LPC_UART->LSR & 0x01) == 1)
			{
					if(LPC_UART->RBR == 255)
					{
						sprintf(GcRcvBuf," 摄氏温度 =%3d  华氏温度=%3d \r\n",temp,temp/5*9+32);
						UART_SendStr(GcRcvBuf);
					}
					else

					{
						sprintf(GcRcvBuf," 信号错误  \r\n");
						UART_SendStr(GcRcvBuf);
					}
				
				}

			}
