/*
 * SAMV71_PMC_CHANGING_CLOCK.c
 *
 * Created: 6/10/2017 1:29:32 PM
 * Author : DucCuong
 */ 


#include "sam.h"
#include "samv71q21.h"

#define NUL '\0'

//page 294
//31.17 
//Programing Sequence for changing clock PLL
void PMC_Changing_clock(void)
{
	//prepare
	EFC->EEFC_WPMR |= EEFC_WPMR_WPEN | EEFC_WPMR_WPKEY_PASSWD;
	EFC->EEFC_FMR |= EEFC_FMR_FWS(5);
	PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD;
	//step 1
	//do nothing
	//step 2
	PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTST(0xFF);
	while((PMC->PMC_SR & PMC_SR_MOSCXTS) == NUL);
	//step 3
	PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;
	//step 4
	while((PMC->PMC_SR & PMC_SR_MOSCSELS) != PMC_SR_MOSCSELS);
	//step 5
	while((PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY) == NUL);
	if(PMC->CKGR_MCFR == NUL )
	{
		PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD |CKGR_MOR_MOSCSEL;
		while((PMC->PMC_SR & PMC_SR_MOSCSELS) != PMC_SR_MOSCSELS);
	}
	//step 6
	PMC->CKGR_PLLAR |= CKGR_PLLAR_DIVA(1) | CKGR_PLLAR_PLLACOUNT(0x3F) | CKGR_PLLAR_MULA(0x18) | CKGR_PLLAR_ONE;
	//step 7
	PMC->PMC_MCKR |= PMC_MCKR_PRES_CLK_1;
	while((PMC->PMC_SR & PMC_SR_MCKRDY) != PMC_SR_MCKRDY);
	PMC->PMC_MCKR |= PMC_MCKR_MDIV_PCK_DIV2;
	while((PMC->PMC_SR & PMC_SR_MCKRDY) != PMC_SR_MCKRDY);
	PMC->PMC_MCKR &= ~PMC_MCKR_CSS(0x1);
	while((PMC->PMC_SR & PMC_SR_MCKRDY) != PMC_SR_MCKRDY);
	PMC->PMC_MCKR |= PMC_MCKR_CSS(0x2);
	while((PMC->PMC_SR & PMC_SR_MCKRDY) != PMC_SR_MCKRDY);
	//step 8
//	PMC->PMC_SCER |= PMC_SCER_PCK4;
//	PMC->PMC_PCK[4] |= PMC_PCK_CSS_PLLA_CLK;	
}

int main(void)
{
    /* Initialize the SAM system */
    //SystemInit();
	PMC_Changing_clock();
    /* Replace with your application code */
    while (1) 
    {
		PMC->PMC_SCER |= PMC_SCER_PCK4;
    }
}
