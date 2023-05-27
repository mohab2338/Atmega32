/*
 * UART.c
 *
 *  Created on: Dec 17, 2022
 *      Author: My-Computer
 */

#define F_CPU 8000000UL
#include "util/delay.h"

#include "BIT_MATH.h"
#include "UART.h"
#include "UART_reg.h"
#include <math.h>
#include "Global_Interrupt_interface.h"
#include "Dio_interface.h"

/* Set baud rate */
//UBRRH = (unsigned char)(baud>>8);
//UBRRL = (unsigned char)baud;
/* Enable receiver and transmitter */
//UCSRB = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 2stop bit */
//UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
#define NULL  ((void *)0)
#define BAUD_ASYNCH_NORMAL(baud)	(((float)F_CPU/(float)(16*baud)) - 1)



void (*UART_pvRxFunction)(void) = NULL;
void (*UART_pvTxFunction)(void) = NULL;


void UART_Init(u32 Baud, u8 numberOfBits, u8 numberOfStopBits, u8 ParityCheck)
{
	DIO_voidSetPinDirection(DIO_u8PORT_D, DIO_u8PIN_0, DIO_u8INPUT);
		DIO_voidSetPinDirection(DIO_u8PORT_D, DIO_u8PIN_1, DIO_u8OUTPUT);
	/* Set baud rate */
	/*Note: The baud rate config can't handle some baud rates due to not using  UBRRH  */
	//UBRRH = (9600 >>8); // i don't understand why this format check it!
	UBRRL = (u8)( round( BAUD_ASYNCH_NORMAL(Baud) ) );
	/* Enable receiver and transmitter */
	SET_BIT(UCSRB, UCSRB_TXEN);
	SET_BIT(UCSRB, UCSRB_RXEN);
	/* Set frame format: data Bits, stop bits */
	SET_BIT(UCSRC,UCSRC_URSEL); /*Select the address location for UCSRC reg */
	if(numberOfBits == _5_Bits)
	{
		CLR_BIT(UCSRC, UCSRC_UCSZ0);
		CLR_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
	}
	else if(numberOfBits == _6_Bits)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		CLR_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
	}
	else if(numberOfBits == _7_Bits)
	{
		CLR_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
	}
	else if(numberOfBits == _8_Bits)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
	}
	else if(numberOfBits == _9_Bits)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		SET_BIT(UCSRB, UCSRB_UCSZ2);
	}
	/* Stop bits configuration */
	if(numberOfStopBits == 1)
	{
		CLR_BIT(UCSRC,UCSRC_USBS);

	}
	else if(numberOfStopBits == 2)
	{
		/*ATTENTION!!! The 2 stop bits mode doesn't give right output i don't know why !!!*/
		SET_BIT(UCSRC,UCSRC_USBS);

	}

	/*****Parity check*********/

	if(ParityCheck == DISABLED)
	{
		CLR_BIT(UCSRC, UCSRC_UPM0);
		CLR_BIT(UCSRC, UCSRC_UPM1);
	}
	else if(ParityCheck == EVEN_PARITY)
	{
		CLR_BIT(UCSRC, UCSRC_UPM0);
		SET_BIT(UCSRC, UCSRC_UPM1);
	}
	else if(ParityCheck == ODD_PARITY)
	{
		SET_BIT(UCSRC, UCSRC_UPM0);
		SET_BIT(UCSRC, UCSRC_UPM1);
	}
	/*Multi-processor Communication mode*/
	if(MULTIPROCESS_COMM_MODE == Enable)
	{
		SET_BIT(UCSRA, UCSRA_MPCM);
	}


}

void UART_Send_character(u8 Data)
{
	while( GET_BIT(UCSRA, UCSRA_UDRE) == 0);
	//CLR_BIT(UCSRB, UCSRB_TXB8); // Clear it 9nth Bit before checking for 9nth data bit
	//if( Data & (0x100) ) GET_BIT(Data, 8) == 1
	//	SET_BIT(UCSRB, UCSRB_TXB8);


	if( Data & (0x0100) )
	{
		SET_BIT(UCSRB, UCSRB_TXB8);
	}
	else
	{
		CLR_BIT(UCSRB, UCSRB_TXB8);
	}
	UDR = Data;

}
void UART_Send_String(char *Data)
{
	while( *Data != '\0'){
		UART_Send_character(*Data);
		//_delay_ms(5);
		Data++;
	}

}
u8 UART_Receive()
{
	u16 RX_DATA=0;

		while(GET_BIT(UCSRA,UCSRA_RXC) == 0 );
		//UCSRA = (0<<5);
		if ( UCSRA_PE == 1 ){
			CLR_BIT(UCSRA, UCSRA_FE);
			return 0;
		}
		//else if( UCSRA_PE == 0 )
		//	return UDR;

		RX_DATA |= (GET_BIT(UCSRB, UCSRB_RXB8)<< 8);
		RX_DATA |= (UDR);

		//UCSRB = (UCSRB >> 1) & 0x01;
		//return ((UCSRB << 8) | UDR);

		if(MULTIPROCESS_COMM_MODE == Enable)
		{
			SET_BIT(UCSRA, UCSRA_MPCM);
		}
		return RX_DATA;
}

u8 UART_SlaveAddressRecive(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0 );
	if( GET_BIT(UCSRA, UCSRA_MPCM) == 1)
    // &&( GET_BIT(UCSRB, UCSRB_RXB8) == 1) )
	{
		if( UDR == SLAVE_ADDRESS)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
 return 0;

}
u8 UART_GetReceivedData(void)
{
	return UDR;
}

void UART_InterruptEnable(u8 TX, u8 RX , u8 Empty_intr)
{
	GlobalInterrupt_Enable();
	if( TX == Enable_TX )
	{
		SET_BIT(UCSRB, UCSRB_TXCIE);
	}
	else
	{
		CLR_BIT(UCSRB, UCSRB_TXCIE);
	}
    if(RX == Enable_RX)
	{
		SET_BIT(UCSRB, UCSRB_RXCIE);
	}
    else
    {
		CLR_BIT(UCSRB, UCSRB_RXCIE);
    }
    if( Empty_intr == Enable_Empty_interrupt)
    {
    	SET_BIT(UCSRB, UCSRB_UDRIE);
    }
    else
    {
    	CLR_BIT(UCSRB, UCSRB_UDRIE);
    }

}
u8 UART_u8RxCompleteSetCallback(void (*Copy_pvINTFunction)(void))
{
	u8 Local_u8ReturnStatus = OK;
		if(Copy_pvINTFunction != NULL)
		{
			UART_pvRxFunction = Copy_pvINTFunction;
		}
		else
		{
			Local_u8ReturnStatus = NOK;
		}
		return Local_u8ReturnStatus;
}

void __vector_13(void)
{
	if( UART_pvRxFunction != NULL)
		{
			UART_pvRxFunction();
		}
}
u8 UART_u8TxCompleteSetCallback(void (*Copy_pvINTFunction)(void))
{
	u8 Local_u8ReturnStatus = OK;
		if(Copy_pvINTFunction != NULL)
		{
			UART_pvTxFunction = Copy_pvINTFunction;
		}
		else
		{
			Local_u8ReturnStatus = NOK;
		}
		return Local_u8ReturnStatus;
}

void __vector_15(void)
{
	if( UART_pvTxFunction != NULL)
		{
			UART_pvTxFunction();
		}
}

