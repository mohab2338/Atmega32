/*
 * UART.h
 *
 *  Created on: Dec 17, 2022
 *      Author: My-Computer
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "std_types.h"

/*configurations Macros*/
#define OK  0
#define NOK  1

#define SLAVE_ADDRESS				0
#define MULTIPROCESS_COMM_MODE     Disable

enum Baud_Rates { BAUD_2400  = 2400,
				  BAUD_4800  = 4800,
                  BAUD_9600  = 9600,
                  BAUD_14400 = 14400,
                  BAUD_19200 = 19200,
                  BAUD_28800 = 28800,
                  BAUD_38400 = 38400,
                  BAUD_57600 = 57600 }; /*Note There are more Baud Rates but i am lazy XD!*/

enum Frame_NumberOfBits { _5_Bits =  5,
						  _6_Bits =  6,
						  _7_Bits =  7,
						  _8_Bits =  8,
						  _9_Bits =  9 };

enum Frame_NumberOfStopBits { _1_Bit = 1,
							  _2_Bits = 2 };


enum Parity_Mode {  DISABLED    = 0,
					EVEN_PARITY = 1,
					ODD_PARITY  = 2 };

enum Multiprocessor_Comm_Mode { Disable = 0,
							    Enable  = 1};

enum RX_TX_Interrupt { Disable_TX = 0 ,
					   Enable_TX  = 1,
					   Disable_RX = 0 ,
					   Enable_RX  = 1,
					   Enable_Empty_interrupt = 1,
					   Disable_Empty_interrupt = 0};

/*RX complete*/
void __vector_13(void)__attribute__((signal));
/*Data register Empty*/
void __vector_14(void)__attribute__((signal));
/*TX complete*/
void __vector_15(void)__attribute__((signal));


void UART_Send_character( u8 Data);
void UART_Send_String(char *Data);
u8 UART_Receive();
u8 UART_GetReceivedData(void);
u8 UART_SlaveAddressRecive(void);
void UART_Init(u32 Baud, u8 numberOfBits, u8 numberOfStopBits, u8 ParityCheck);

void UART_InterruptEnable(u8 TX, u8 RX , u8 Empty_intr);

u8 UART_u8RxCompleteSetCallback(void (*Copy_pvINTFunction)(void));
u8 UART_u8TxCompleteSetCallback(void (*Copy_pvINTFunction)(void));

#endif /* UART_UART_H_ */
