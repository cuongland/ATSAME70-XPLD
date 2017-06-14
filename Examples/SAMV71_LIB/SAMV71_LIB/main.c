/*
 * SAMV71_LIB.c
 *
 * Created: 6/11/2017 10:02:11 PM
 * Author : DucCuong
 */ 

#include "sam.h"
#include "samv71q21.h"
#include "UART3_debug.h"
#include "System_Init.h"

void SysTick_Handler(void)
{
	//toggle the led at PC8
	PIOC->PIO_ODSR ^= PIO_ODSR_P9;
}

int main(void)
{
    /* Initialize the SAM system */
    System_Init();
	//UART_init();
	
	//Systick configure
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |	SysTick_CTRL_ENABLE_Msk;
	SysTick->LOAD = 0xFFFFFF;
	
	//configure the pin for output
	PIOC->PIO_OER |= PIO_OER_P9;
	
	//enable PIOC control
	PIOC->PIO_PER |= PIO_PER_P9;
	
	//disable resister pull-up
	PIOC->PIO_PUDR |= PIO_PUDR_P9;
	
	//on page 350, in 32.5.5 Synchronous Data Output
	//if i want to read/write on PIO_ODSR, then PIO_OWER must be set
	//once it is done, the PIO_ODSR can use as a regular register
	//-> ignore checking the PIO_ODSR to set or clear regiester.
	PIOC->PIO_OWER |= PIO_OWER_P9;
	
	//set global interrupt
	__asm(" cpsie	i");

    /* Replace with your application code */
    while (1) 
    {
		//UART_Transmit();
    }
}
