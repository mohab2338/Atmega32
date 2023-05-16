/*************************************************
*  FILE  DESCRIPTION
*------------------------------------------------
*     File: main.c
*     Description: Application on Graphical LCD
*
****************************************************/

#define F_CPU 8000000UL				/* Define CPU clock Frequency 8MHz */
#include <util/delay.h>
#include "std_types.h"
#include "BIT_MATH.h"
#include "GLCD_interface.h"
#include "Dio_interface.h"
#include "KPAD.h"



int main(void)
{

	char y[50];
    GLCD_VoidInit();
    KPAD_Init();
    GLCD_voidClearScreen();
	GLCD_voidSendString(0, "Welcome Mohab");

	while(1)
	{
	 y[0] = KPAD_Read();
	 GLCD_voidSendString(1, y);
	}
}

