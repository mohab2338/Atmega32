/*
 * Timer2_registers.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Omar
 */

#ifndef TIMER2_REGISTERS_H_
#define TIMER2_REGISTERS_H_

#define TCCR2					*((volatile u8*)0x45)
#define TCCR2_CS20						0
#define TCCR2_CS21						1
#define TCCR2_CS22  						2
#define TCCR2_COM20						4
#define TCCR2_COM21						5
#define TCCR2_WGM20						6
#define TCCR2_WGM21						3

#define TCNT2				*((volatile u8*)0x44)


#define OCR2				*((volatile u8*)0x43)


#define ASSR				*((volatile u8*)0x42)
#define ASSR_AS2						3 //1 --> clock from crystal

#define TIMSK				*((volatile u8*)0x59)
#define TIMSK_TOIE2					6
#define TIMSK_OCIE2					7

#define TIFR				*((volatile u8*)0x58)
#define TIFR_OCF2					7
#define TIFR_TOV2					6
#endif /* TIMER2_REGISTERS_H_ */
