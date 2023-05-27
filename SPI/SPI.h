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


enum Master_Or_Slave{ SPI_Slave = 0,
					  SPI_Master = 1};

enum SCK_Frequency{ SPI_FOS_4  = 0,
					SPI_FOS_64 = 1};

enum SPI_Interrupt{ SPI_Inerrupt_Enabled = 0,
					SPI_Inerrupt_Disabled =1
					};

void __vector_12(void)__attribute__((signal));

void SPI_Init(u8 Master_Or_Slave, u8 CLK_Rate, u8 Enable_Interrupt );
u8 SPI_Send(u8 Data);
void SPI_Send_String(char *Data);

u8 SPI_Receive();
u8 SPI_GetReceivedData();


u8 SPI_CallBack_Fn( void (* Handler_Fn)(void) );




#endif /* SPI_H_ */
