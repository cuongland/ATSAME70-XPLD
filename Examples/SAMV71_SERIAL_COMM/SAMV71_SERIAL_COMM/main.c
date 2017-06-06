/*
 * SAMV71_SERIAL_COMM.c
 *
 * Created: 6/5/2017 10:36:55 PM
 * Author : DucCuong
 */ 


#include "sam.h"
#include "samv71q21.h"

void UART_init(void)
{
	//reset everything
	UART3->UART_CR |=  UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS ;	
	UART3->UART_MR |= UART_MR_BRSRCCK;
	UART3->UART_BRGR |= 0x4E;
	UART3->UART_CR |= UART_CR_TXEN;
}

void UART_Transmit(void)
{
	UART3->UART_THR = 0x61;
	while((UART3->UART_SR & UART_SR_TXRDY)!=UART_SR_TXRDY);
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	UART_init();
	UART_Transmit();
    /* Replace with your application code */
    while (1) 
    {
	//	UART_Transmit();
    }
}
