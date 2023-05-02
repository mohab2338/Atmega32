/*
 * main.c
 * 
 * X10 Protocol Code
 * 
 */

#define F_CPU 8000000UL
#include "util/delay.h"

#include "std_types.h"
#include "BIT_MATH.h"

#include "Dio_interface.h"
#include "EXTI_interface.h"
#include "Timer1_interface.h"
#include "LCD_interface.h"
#include "Watch_Dog_Timer_interface.h"
#include "Global_Interrupt_interface.h"


#define DATAWIDTH  12
#define STORAGE		4

#define WRITETIME  1000
#define READTIME	350


#define RECEIVEPORT		DIO_u8PORT_B
#define RECEIVEPIN		DIO_u8PIN_0

#define SIGNALPORT		DIO_u8PORT_D
#define SIGNALPIN		DIO_u8PIN_5

#define BUTTONSPORT			DIO_u8PORT_A
#define BUTTONSPINSVALUE	0x00

void Send(u8 Copy_Cross);
void Pulse(u8 Copy_BitValue);
void WelcomeChoices();
void ZeroCrossing();
void Devices(void);
void ZCD(void);
static u8 Data[STORAGE][DATAWIDTH] = { {1,0,0,0, 0,0,0,0, 0,0,0,0}
									  ,{1,1,1,1, 0,1,0,0, 1,0,0,1}
									  ,{1,1,1,1, 0,0,1,0, 0,1,0,0}
									  ,{1,1,1,1, 0,0,0,1, 1,1,0,0} };
static u8 status[4] = {0,0,0,0};
static u8 CrossingCounter = 0;
static u8 DataType = 0;
int main(void)
{
/*activate LCD screen*/
	LCD_voidInit();
/*activate i/p and o/p Pins*/
	DIO_voidSetPortDirection(BUTTONSPORT,BUTTONSPINSVALUE);//input Pins
	DIO_voidSetPinDirection(SIGNALPORT,SIGNALPIN,DIO_u8OUTPUT);//signal 120k
	DIO_voidSetPinDirection(RECEIVEPORT,RECEIVEPIN,DIO_u8INPUT);// Receive Pin
/*external interrupt */
	EXTI_u8INT0SetCallback(ZeroCrossing);
	EXTI0_voidInit(EXTI_RISING_EDGE);
/*enable Timer1 for transmit signal*/
	Timer1_voidInit();
/*disable global interrupt */
	GlobalInterrupt_Disable();
	while(1)
	{
		WelcomeChoices();
	}
}

void WelcomeChoices()
{
static u8 input = 0;
	LCD_voidClearScreen();
	LCD_voidGotoxy(0,0);
	LCD_voidSendString(" Welcome home : ");
	LCD_voidGotoxy(1,0);
	LCD_voidSendString("1-menu ");
	LCD_voidGotoxy(2,0);
	LCD_voidSendString("2-exit ");

	while( (input=DIO_u8GetPortValue(BUTTONSPORT) )==0)
	{
		//wait till input not zero
	}

	switch( input )
	{
	case 1:
		Devices();

		while(DIO_u8GetPinValue(DIO_u8PORT_D,DIO_u8PIN_2)==1)
		{
				//wit until int2 pin == 0 i.e. the next zero crossing edge
		}
		GlobalInterrupt_Enable();
		break;

	case 2:
		LCD_voidClearScreen();
		LCD_voidSendString(" Exited");
		LCD_voidGotoxy(1,0);
	    LCD_voidSendString(" 1 to start");
		while( DIO_u8GetPortValue(BUTTONSPORT)!= 1)
		{
			//wait till started
		}
		break;

	}//end switch 1

}
void Devices(void)
{
	_delay_ms(500/8);
	static u8 press = 0;
	LCD_voidClearScreen();
	if(status[0]==0) LCD_voidSendString(" 1-device 1 is off");
	else			 LCD_voidSendString(" 1-device 1 is on");
	LCD_voidGotoxy(1,0);
	if(status[1]==0) LCD_voidSendString(" 2-device 2 is off");
	else			 LCD_voidSendString(" 2-device 2 is on");
	LCD_voidGotoxy(2,0);
	if(status[3]==0) LCD_voidSendString(" 3-device 3 is off");
	else			 LCD_voidSendString(" 3-device 3 is on");
	LCD_voidGotoxy(3,0);
	LCD_voidSendString(" 4-back");


	while( (press = (DIO_u8GetPortValue(BUTTONSPORT)) ) == 0)
	{
		//wait till button pressed
	}

	switch( press )
	{
	case 1:
		DataType = press;
		break;
	case 2:
		DataType = press;
		break;
	case 4:
		DataType = press;
		break;
	case 8://back
	break;
	}//end switch 2
}
void ZeroCrossing()
{

	while(DIO_u8GetPinValue(DIO_u8PORT_D,DIO_u8PIN_2)==0)
	{
		//wait till the rising edge
	}
	if( (DataType <= STORAGE ) )
	{
		switch(DataType  )
		{
		case 1:
			Send(1);
			break;
		case 2:
			Send(2);
			break;
		case 4:
			Send(3);
			break;
		}//End switch
	}//End if

}
void Send(u8 Copy_DataType)
{

	Pulse( Data[Copy_DataType][CrossingCounter] ); //enables the OC0 pin
	CrossingCounter++;

	if(CrossingCounter == DATAWIDTH)
	{
		CrossingCounter = 0;
		GlobalInterrupt_Disable();

		while(DIO_u8GetPinValue(DIO_u8PORT_D,DIO_u8PIN_2) == 1)
		{
			//wait till falling edge then receive check bit
		}
		_delay_us(READTIME);

		if(DIO_u8GetPinValue(RECEIVEPORT,RECEIVEPIN)==1)
		{
			status[DataType-1] = !status[DataType-1];
		}
		DataType = 0;

	}

}
void Pulse(u8 Copy_BitValue)
{
	Timer1_SetCompareMatchA_Value((8000000/(2*129000))-1);
	Timer1PWM_A_OC1A( Copy_BitValue );
	_delay_us(WRITETIME);
	Timer1PWM_A_OC1A( 0 );
}
void ZCD(void)
{
	static u8 state=0;
	if(state == 0)
	{
	DIO_voidSetPinValue(DIO_u8PORT_D,DIO_u8PIN_7,DIO_u8HIGH);
	state = 1;
	}
	else
	{
		DIO_voidSetPinValue(DIO_u8PORT_D,DIO_u8PIN_7,DIO_u8LOW);
		state =0;
	}

}
