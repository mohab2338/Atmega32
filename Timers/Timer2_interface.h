/*
 * Timer2_interface.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Omar
 */

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_


#define OVERFLOW			0
#define CTC					1
#define FAST_PWM			2
#define PHASE_CORRECT_PWM   3


void Timer2_voidInit(void);
void Timer2_SetComMatchValue(u8 Copy_CompareValue);
void Timer2_DisableOC2(void);
void Timer2_EnableOC2(void);
void Timer2PWM_Pulse(u8 Copy_BitValue);

#endif /* TIMER2_INTERFACE_H_ */
