/*
 * SPI.h
 *
 *  Created on: Dec 23, 2022
 *      Author: My-Computer
 */

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"

#define SPCR			(*(volatile u8*)0x2D)
#define SPCR_SPR0		0
#define SPCR_SPR1		1
#define SPCR_CPHA		2
#define SPCR_CPOL		3
#define SPCR_MSTR		4
#define SPCR_DORD		5
#define SPCR_SPE		6
#define SPCR_SPIE		7


#define	SPSR				(*(volatile u8*)0x2E)
#define	SPSR_SPI2X				0
#define	SPSR_WCOL				6
#define	SPSR_SPIF				7

/********Data Register********/
#define	SPDR				(*(volatile u8*)0x2F)


enum Master_Or_Slave{ Slave = 0,
					  Master = 1};

enum SCK_Frequency{ FOS_4  = 0,
					FOS_64 = 1};



void SPI_Init(u8 Master_Or_Slave, u8 CLK_Rate );
u8 SPI_Send(u8 Data);
void SPI_Send_String(char *Data);

u8 SPI_Receive();

//void __vector_12(void);
//u8 SPI_CallBack_Fn( void (* Handler_Fn)(void) );




#endif /* SPI_H_ */
