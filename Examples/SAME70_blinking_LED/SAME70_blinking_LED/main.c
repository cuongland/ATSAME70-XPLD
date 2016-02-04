/*
 * SAME70_blinking_LED.c
 *
 * Created: 2/4/2016 10:21:36 AM
 * Author : Duc Cuong Dinh
 * Purpose: say "Hello World"
 * Using: Systick
 */ 
#include "sam.h"
#include "same70q21.h"

void SysTick_Handler(void)
{
	//toggle the led at PC8
	PIOC->PIO_ODSR ^= PIO_ODSR_P8;
}

int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	
	//Systick configure
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |	SysTick_CTRL_ENABLE_Msk;
	SysTick->LOAD = 0xFFFFFF;
	
	//configure the pin for output
	PIOC->PIO_OER |= PIO_OER_P8;
	
	//enable PIOC control
	PIOC->PIO_PER |= PIO_PER_P8;
	
	//disable resister pull-up
	PIOC->PIO_PUDR |= PIO_PUDR_P8;
	
	//on page 350, in 32.5.5 Synchronous Data Output
	//if i want to read/write on PIO_ODSR, then PIO_OWER must be set
	//once it is done, the PIO_ODSR can use as a regular register
	//-> ignore checking the PIO_ODSR to set or clear regiester.
	PIOC->PIO_OWER |= PIO_OWER_P8;
	
	//set global interrupt
	__asm(" cpsie	i");
	
	while (1)
	{
	}
}
