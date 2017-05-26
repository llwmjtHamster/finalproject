#include "LPC11xx.h"
#include "ADC.h"
void ADC_Init(void)
	{
		LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
		LPC_IOCON->R_PIO0_11 &= ~0xBF;
		LPC_IOCON->R_PIO0_11 |= 0x02;
		LPC_SYSCON->PDRUNCFG &=~(0x01<<4);
		LPC_SYSCON->SYSAHBCLKCTRL |=(0x01<<13);
		LPC_ADC->CR=(0x01<<0)|
		((SystemCoreClock/1000000-1)<<8)|
		(0<<16)|
		(0<<17)|
		(0<<24)|
		(0<<27);
	}