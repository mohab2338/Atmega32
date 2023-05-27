/*
 * SPI.c
 *
 *  Created on: Dec 23, 2022
 *      Author: My-Computer
 */

#define F_CPU 8000000UL
#include "BIT_MATH.h"
#include "SPI.h"
#include "DIO_interface.h"
#include "Global_Interrupt_interface.h"

#define SPI_PORT	DIO_u8PORT_B
#define MOSI		DIO_u8PIN_5
#define MISO		DIO_u8PIN_6
#define SCK		    DIO_u8PIN_7
#define SS			DIO_u8PIN_4

#define NULL   (void*)0
void  (*SPI_FunctionPointer)(void) = NULL;

void SPI_Init(u8 Master_Or_Slave, u8 CLK_Rate, u8 Enable_Interrupt )
{
	/********* Choose Master or Slave ********/
	if( Master_Or_Slave == SPI_Master )
	{
		SET_BIT(SPCR, SPCR_MSTR);
		DIO_voidSetPinDirection(SPI_PORT, MOSI, DIO_u8OUTPUT);
		DIO_voidSetPinDirection(SPI_PORT, SCK , DIO_u8OUTPUT);
		DIO_voidSetPinDirection(SPI_PORT, MISO, DIO_u8INPUT );
	}
	else if( Master_Or_Slave == SPI_Slave)
	{
		CLR_BIT(SPCR, SPCR_MSTR);
		DIO_voidSetPinDirection(SPI_PORT, MOSI, DIO_u8INPUT  );
		DIO_voidSetPinDirection(SPI_PORT, SCK , DIO_u8INPUT  );
		DIO_voidSetPinDirection(SPI_PORT, MISO, DIO_u8OUTPUT );

		DIO_voidSetPinDirection(SPI_PORT, SS, DIO_u8INPUT );
	}
	/********* Choose Frequency ********/
	if( CLK_Rate == SPI_FOS_4 )
	{
		CLR_BIT(SPCR, SPCR_SPR0);
		CLR_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
	}
	else if( CLK_Rate == SPI_FOS_64)
	{
		CLR_BIT(SPCR, SPCR_SPR0);
		SET_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);

	}

	/*Enable interrupt */
	if(Enable_Interrupt == SPI_Inerrupt_Enabled)
	{
		GlobalInterrupt_Enable();
		SET_BIT(SPCR, SPCR_SPIE);
	}
	/********* SPI Enable  ********/
	SET_BIT(SPCR, SPCR_SPE);
}



u8 SPI_CallBack_Fn( void (* Handler_Fn)(void) )
{

	if( Handler_Fn != NULL){
		SPI_FunctionPointer = Handler_Fn;
	}
	else{
		return -1;
	}
	return -1;
}

void __vector_12(void)
{

	if( SPI_FunctionPointer != NULL){

		//CLR_BIT(SPSR, SPSR_SPIF);
		SPI_FunctionPointer();
	}


}
u8 SPI_Send(u8 Data)
{
	/********* SPI Enable  ********/
	//SET_BIT(SPCR, SPCR_SPE);
	SPDR = Data;
	while( GET_BIT(SPSR, SPSR_SPIF) == 0 );
	//CLR_BIT(SPCR, SPCR_SPE);
	//CLR_BIT(SPSR, SPSR_SPIF);
	return SPDR;

}
void SPI_Send_String(char *Data)
{
	while( *Data != '\0'){
		SPI_Send(*Data);
		Data++;
	}

}


u8 SPI_Receive()
{
	while( GET_BIT(SPSR, SPSR_SPIF) == 0);
	return SPDR;
}
u8 SPI_GetReceivedData()
{
	return SPDR;
}
