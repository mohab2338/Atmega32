/*
 * UltraSonic.c
 *
 *  Created on: May 27, 2023
 *      Author: My-Computer
 */
#include "util/delay.h"
#include <math.h>
#include "E:\repos\Atmega32-16\Atmega32\Lib\std_types.h"
#include "E:\repos\Atmega32-16\Atmega32\Lib\BIT_MATH.h"
#include "E:\repos\Atmega32-16\Atmega32\DIO\DIO_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\Timers\Timer1_interface.h"
#include "E:\repos\Atmega32-16\Atmega32\LCD\LCD_interface.h"
#include "UltraSonic.h"
#include "UltraSonic_Config.h"

 f32 Distance = 0;

void US_Sensor_VoidInit(void)
{
	/*Set Input Capture Pin as Input*/
	DIO_voidSetPinDirection(DIO_u8PORT_D,DIO_u8PIN_6, DIO_u8INPUT);
	/*Set Pin As Trigger for the Sensor*/
	DIO_voidSetPinDirection(US_Senor_TR_PORT,US_Senor_TR_PIN, DIO_u8OUTPUT);
	/*Set Callback Function */
	Timer1ICP_u8ICPtimerCallback(US_Senor_VoidDistanceMeasure);
	/*Initialize Input Capture Interrupt */
	Timer1_ICP1_INT_Enable(RisingEdge);
	/*Initialize Timer1
	 * Note !! Set Timer1 On Normal mode of CTC mode in Timer1 Config File */
	Timer1_voidInit();

}
void US_Senor_VoidDistanceMeasure()
{
	static u8 Level = RisingEdge;
	f32 Timer_counter_value = 0;

	if(Level == RisingEdge)
	{
		Timer1_SetTimer1value(0);
		Timer1_ICP1_INT_Enable(FallingEdge);
		Level = FallingEdge;
	}
	else if(Level == FallingEdge)
	{
		Timer_counter_value = Timer1_u16GetICPValue();
		Distance= (Timer_counter_value * 0.000001) * 340;

#if(LCD_USED_16x2 == _USE_LCD)
		u32 y = 0;
		LCD_VoidDisplayInteger( Distance);
		LCD_voidSendData('.');
		y = round( ( (Distance - (u32)(Distance) ) *100));
		LCD_VoidDisplayInteger(y);
		LCD_voidSendData('m');
#endif

		Timer1_ICP1_INT_Enable(RisingEdge);
		Level = RisingEdge;
	}

}

void US_Sensor_VoidTriggerPulse()
{
	DIO_voidSetPinValue(US_Senor_TR_PORT, US_Senor_TR_PIN, DIO_u8HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(US_Senor_TR_PORT, US_Senor_TR_PIN, DIO_u8LOW);
}
