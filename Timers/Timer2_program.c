/*
 * Timer2_program.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Omar
 */

#include "util/delay.h"

#include "std_types.h"
#include "BIT_MATH.h"

#include "Dio_interface.h"
#include "Global_Interrupt_interface.h"
#include "Timer2_registers.h"
#include "Timer2_interface.h"
#include "Timer2_config.h"


void Timer2_voidInit(void)
{
#if(TIMER_MODE == OVERFLOW)
	GlobalInterrupt_Enable();
/*choose fast PWM*/
	SET_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);
/*enable or disable OC2*/
	CLR_BIT(TCCR2,TCCR2_COM20);
	CLR_BIT(TCCR2,TCCR2_COM21);
/*clk prescaler */
	SET_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS22);
/*enable async*/
	SET_BIT(ASSR,ASSR_AS2);
#elif(TIMER_MODE == PHASE_CORRECT_PWM)
	/*choose Fast PWM mode */
		SET_BIT(TCCR2,TCCR2_WGM20);
		CLR_BIT(TCCR2,TCCR2_WGM21);
		/*activate OC0*/
		CLR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		/*clk prescaler */
		SET_BIT(TCCR2,TCCR2_CS20);
		CLR_BIT(TCCR2,TCCR2_CS21);
		CLR_BIT(TCCR2,TCCR2_CS22);
}
#endif

void Timer2_SetComMatchValue(u8 Copy_CompareValue)
{

	OCR2 = Copy_CompareValue;


}
void Timer2_EnableOC2(void)
{
	CLR_BIT(TCCR2,TCCR2_COM20);
    SET_BIT(TCCR2,TCCR2_COM21);
}
void Timer2_DisableOC2(void)
{
	CLR_BIT(TCCR2,TCCR2_COM20);
	CLR_BIT(TCCR2,TCCR2_COM21);
}
void Timer2PWM_Pulse(u8 Copy_BitValue)
{

	if(Copy_BitValue == 1)
	{
		CLR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
	}
	else if(Copy_BitValue == 0)
	{
		CLR_BIT(TCCR2,TCCR2_COM20);
		CLR_BIT(TCCR2,TCCR2_COM21);
	}
}
