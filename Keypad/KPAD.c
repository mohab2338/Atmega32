/*
 * KPAD.c
 *
 *  Created on: Dec 16, 2022
 *      Author: My-Computer
 */

#include "std_types.h"
#include "BIT_MATH.h"
#include "Dio_interface.h"
#include "KPAD.h"
#include "util/delay.h"

u16 Key_Pressed[4][4] = { {'7','8','9','/'},
						  {'4','5','6','*'},
					      {'1','2','3','-'},
					      {'c','0','=','+'}  };

u8 KPAD_Init()
{

	u8 Local_check = SUCCSSES;

	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_0, DIO_u8OUTPUT);
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_1, DIO_u8OUTPUT);
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_2, DIO_u8OUTPUT);
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_3, DIO_u8OUTPUT);

	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_4, DIO_u8INPUT );
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_5, DIO_u8INPUT );
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_6, DIO_u8INPUT );
	DIO_voidSetPinDirection(KPAD_PORT, DIO_u8PIN_7, DIO_u8INPUT );

	return Local_check;

}

u16 KPAD_Read(){

	u8 Row = 0;
	u8 Column = 0;
	u8 local_check = SUCCSSES;

	while(DIO_u8GetNibbleValue(KPAD_PORT, DIO_u8UPPER) == 0)
	{

		for( Row = 0; Row < 4 ; Row++)
		{
			DIO_voidSetPinValue(KPAD_PORT, Row ,DIO_u8HIGH );
			for( Column = (0 + 4) ;Column < (4+4) ; Column++)
			{
				if(DIO_u8GetPinValue(KPAD_PORT, Column) == 1)
				{
					DIO_voidSetPinValue(KPAD_PORT, Row ,DIO_u8LOW );
					_delay_ms(300);// time between two presses
					return Key_Pressed[Row][Column-4];
				}
				else
				{
					//check next Column
				}
			}
			DIO_voidSetPinValue(KPAD_PORT, Row ,DIO_u8LOW );

		}//end for
	}//end while check


	return local_check;


}//End KPAD_Read
