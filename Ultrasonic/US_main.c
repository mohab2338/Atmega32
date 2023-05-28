/*
 * US_main.c
 *
 *  Created on: May 27, 2023
 *      Author: My-Computer
 */

#define F_CPU 8000000UL
#include "util/delay.h"
#include <math.h>
#include "E:\repos\Atmega32-16\Atmega32\Global_Intr\Global_Interrupt_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Lib\std_types.h"
#include "E:\repos\Atmega32-16\Atmega32\Lib\BIT_MATH.h"
#include "E:\repos\Atmega32-16\Atmega32\DIO\DIO_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\ADC\ADC_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\LCD\LCD_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Timers\Timer1_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\External_interrupt\EXTI_interface.h"

#include "UltraSonic.h"

int main(void)
{

	DIO_voidSetPinDirection(DIO_u8PORT_A,DIO_u8PIN_5, DIO_u8INPUT); // Pin to start measuring
	LCD_voidInit();
	US_Sensor_VoidInit();

	while(1)
	{
		if(DIO_u8GetPinValue(DIO_u8PORT_A,DIO_u8PIN_5) == 1)
		{
			US_Sensor_VoidTriggerPulse();
			_delay_ms(500);
			LCD_voidClearScreen();
			LCD_VoidDisplayFloat(Distance);
		}
	}
}


