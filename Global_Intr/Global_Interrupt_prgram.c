/*
 * Global_Interrupt_prgram.c
 *
 *  Created on: 24 Aug 2021
 *      Author: omar
 */

#include "E:\repos\Atmega32-16\Atmega32\Lib\std_types.h"
#include "E:\repos\Atmega32-16\Atmega32\Lib\BIT_MATH.h"
#include "E:\repos\Atmega32-16\Atmega32\Global_Intr\Global_Interrupt_reg.h"


void GlobalInterrupt_Enable(void)
{
	SET_BIT(SREG,SREG_I);
}
void GlobalInterrupt_Disable(void)
{
	CLR_BIT(SREG,SREG_I);
}
