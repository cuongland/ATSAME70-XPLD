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

int main(void)
{
    /* Initialize the SAM system */
    System_Init();
	UART_init();

    /* Replace with your application code */
    while (1) 
    {
		UART_Transmit();
    }
}
