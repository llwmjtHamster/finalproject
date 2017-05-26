#include "LPC11xx.h"
#include <stdio.h>
#include "UART.h"
char GcRcvBuf[20];
int temp;
void UART_Init(void)
{
    uint16_t usFdiv;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16); //��IOCON����ʱ��
    LPC_IOCON->PIO1_6  &= ~0x07;
    LPC_IOCON->PIO1_6  |= (1<<0); //����P1.6ΪRXD 
    LPC_IOCON->PIO1_7  &= ~0x07;
    LPC_IOCON->PIO1_7  |= (1<<0); //����P1.7ΪTXD 
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12); //��UART���ܲ���ʱ�� 
    LPC_SYSCON->UARTCLKDIV = 0x01;  //UARTʱ�ӷ�Ƶ 
    
    LPC_UART->LCR  = 0x83; // �������ò�����  
    usFdiv = (SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS; //���ò�����
    LPC_UART->DLM  = usFdiv / 256;
    LPC_UART->DLL  = usFdiv % 256; 
    LPC_UART->LCR  = 0x03; // ���������� 
    LPC_UART->FCR  = 0x07;
}
void UART_SendByte(uint8_t ucDat)
{
    LPC_UART->THR = ucDat; //д������
    while ((LPC_UART->LSR & 0x40) == 0); //�ȴ����ݷ������
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
						sprintf(GcRcvBuf," �����¶� =%3d  �����¶�=%3d \r\n",temp,temp/5*9+32);
						UART_SendStr(GcRcvBuf);
					}
					else

					{
						sprintf(GcRcvBuf," �źŴ���  \r\n");
						UART_SendStr(GcRcvBuf);
					}
				
				}

			}
