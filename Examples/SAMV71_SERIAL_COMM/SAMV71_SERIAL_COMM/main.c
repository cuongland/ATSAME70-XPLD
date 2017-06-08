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
	//diable pin PD28 and PD30
	PIOD->PIO_PDR |= PIO_PDR_P28 | PIO_PDR_P30;
	//Power Management Controller for UART3
	PMC->PMC_PCER1 |= PMC_PCER1_PID45;
	//reset everything
	UART3->UART_CR |=  UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;		
	//reset interrupt
	UART3->UART_IDR |= UART_IDR_RXRDY | UART_IDR_TXRDY | UART_IDR_OVRE | UART_IDR_FRAME | UART_IDR_PARE | UART_IDR_TXEMPTY | UART_IDR_CMP;
	//setting mode
	UART3->UART_MR |= UART_MR_PAR_NO;
	//baud rate 115200
	UART3->UART_BRGR |= 78;
	//enable transmit and receive
	UART3->UART_CR |= UART_CR_TXEN | UART_CR_RXEN;		
}

void UART_Transmit(void)
{
	while((!(UART3->UART_SR & UART_SR_TXEMPTY)) && (!(UART3->UART_SR & UART_SR_TXEMPTY))); 
	UART3->UART_THR = 0x61;	
	while((UART3->UART_SR & UART_SR_TXEMPTY) != UART_SR_TXEMPTY);
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	UART_init();
	//UART_Transmit();
    /* Replace with your application code */
    while (1) 
    {
		UART_Transmit();
    }
}
