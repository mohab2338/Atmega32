/*
 * Timer2_program.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Omar
 */

#include "util/delay.h"

#include "E:\repos\Atmega32-16\Atmega32\Lib\std_types.h"
#include "E:\repos\Atmega32-16\Atmega32\Lib\BIT_MATH.h"

#include "E:\repos\Atmega32-16\Atmega32\DIO\Dio_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Global_Intr\Global_Interrupt_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Timers\Timer2_registers.h"
#include "E:\repos\Atmega32-16\Atmega32\Timers\Timer2_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Timers\Timer2_config.h"
//#include "Global_Interrupt_reg.h"
#define NULL  (void*)0

void (*OVTimer2_PvOVTimerfn)(void) = NULL;
void Timer2_voidInit(void)
{
#if(TIMER_MODE == OVERFLOW)

/*choose fast PWM*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);
/*enable or disable OC2*/
	CLR_BIT(TCCR2,TCCR2_COM20);
	CLR_BIT(TCCR2,TCCR2_COM21);
/*clk prescaler */
	SET_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS22);
/*Disable async*/
	CLR_BIT(ASSR,ASSR_AS2);
	/*Enable Overflow Interrupt*/
	SET_BIT(TIMSK, TIMSK_TOIE2);
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
#endif
		GlobalInterrupt_Enable();
		//SET_BIT(SREG,SREG_I);
}


void Timer2_VoidOV_CallBack_fn(void (*Copy_OvTimer2Fn)(void) )
{
	if(Copy_OvTimer2Fn != NULL)
	{
		OVTimer2_PvOVTimerfn = Copy_OvTimer2Fn;
	}
}

void __vector_5(void)
{
	//static u16 counter = 0;

	//counter++;
	//if(counter >= 3060)
	//{
		if(OVTimer2_PvOVTimerfn != NULL)
			{
				OVTimer2_PvOVTimerfn();
			}
	//	counter = 0;
	//}


}
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
