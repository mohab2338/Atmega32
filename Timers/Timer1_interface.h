/*
 * Timer1_interface.h
 *
 *  Created on: Feb 20, 2022
 *      Author: mhy
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#define OK    0
#define NOK	  1
#define OVERFLOW		0
#define CTC_A			1
#define FAST_PWM		2

enum States {Active = 1 , Inactive = 0};
enum SenseLevel {RisingEdge = 1 , FallingEdge = 0};


void Timer1_voidInit(void);

u8 Timer1OV_u8OVtimerCallback(void (*Copy_pvOVTimer1Function)(void));
u8 Timer1CTCA_u8CTCtimerCallback(void (*Copy_CTCTimer1Function)(void));
u8 Timer1ICP_u8ICPtimerCallback(void (*Copy_ICPTimer1Function)(void));

void Timer1_SetCompareMatchA_Value(u16 Copy_CompareValue);
void Timer1_SetTimer1value(u16 Copy_TimerValue);
u16 Timer1_GetTimer1Value(void);

void Timer1PWM_A_OC1A(u8 Copy_BitValue);
void Timer1CTC_A_OC1A(u8 Copy_PinState);
void Timer1CTC_A_Enable_Disable(u8 Copy_u8State);
void Timer1_ICP1_INT_Enable(u8 Copy_u8SenseLevel);
u16 Timer1_u16GetICPValue();

void __vector_6(void)__attribute__((signal));// Input capture unit Atmega32
void __vector_7(void)__attribute__((signal));
void __vector_9(void)__attribute__((signal));


#endif /* TIMER1_INTERFACE_H_ */
