/*************************************************
*  FILE  DESCRIPTION
*------------------------------------------------
*     File: GLCD.c
*     Description: Contains functions of Graphical LCD
*
****************************************************/
#include "util/delay.h"
#include "std_types.h"

#include "BIT_MATH.h"
#include "Dio_interface.h"
#include "GLCD_Font_Header.h"

#include "GLCD_interface.h"

/*======================================================================================*
 *======================================================================================*/

void GLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*1. Set RS with Low --> for command */
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, DIO_u8LOW);
	/*2. Set RW to Low to write          */
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, DIO_u8LOW);
	/*3. Set Command on data Pins 		 */
	DIO_voidSetPortValue(GLCD_DATA_PORT, Copy_u8Command);
	/*4. Send Enable Pulse	(min 1us)	 */
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_EN_PIN, DIO_u8HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_EN_PIN, DIO_u8LOW);

}
/*======================================================================================*
 *======================================================================================*/
void GLCD_voidSendData(u8 Copy_u8Data)
{

	/*1- set RS with HIGH --> for data */
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, DIO_u8HIGH);
	/*2- set RW to low to write*/
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, DIO_u8LOW);
	/*3- set Data on data pins*/
	DIO_voidSetPortValue(GLCD_DATA_PORT, Copy_u8Data);
	/*4- send enable pulse*/
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_EN_PIN, DIO_u8HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_EN_PIN, DIO_u8LOW);
}
/*======================================================================================*
 *======================================================================================*/
void GLCD_VoidInit()
{
 /*1. Set Direction of Pins*/
	DIO_voidSetPortDirection(GLCD_DATA_PORT, 0xFF);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_CS1_PIN,DIO_u8HIGH);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_CS2_PIN,DIO_u8HIGH);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_RS_PIN ,DIO_u8HIGH);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_RW_PIN ,DIO_u8HIGH);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_EN_PIN ,DIO_u8HIGH);
	DIO_voidSetPinDirection(GLCD_CTRL_PORT, GLCD_RST_PIN,DIO_u8HIGH);
 /*2. Select both left & right half of display & Keep reset pin high*/
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8HIGH);
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8HIGH);
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_RST_PIN, DIO_u8HIGH);
	_delay_ms(20);
 /*3. Set Addresses of Display*/
	GLCD_voidSendCommand(0x3E);				/*Display OFF*/
	GLCD_voidSendCommand(0x40);				/*Set Y address    (column     = 0)*/
	GLCD_voidSendCommand(0xB8);				/*Set X address    (Page       = 0)*/
	GLCD_voidSendCommand(0xC0);				/*Set Line address (Start line = 0)*/
	GLCD_voidSendCommand(0x3F);				/*Display ON*/

}
/*======================================================================================*
 *======================================================================================*/
void GLCD_voidClearScreen()
{
	u8 i,j;
	/*Select two segments for clear*/
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8HIGH);
	DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8HIGH);
	for(i=0 ; i < TOTAL_PAGES ; i++)
	{
		GLCD_voidSendCommand((0xB8)+i);   /* Increment page each 64 column*/
		for(j = 0; j < 64; j++)
		{
			GLCD_voidSendData(0);		  /*Write Zeros to all 64 Columns */
		}
	}
	GLCD_voidSendCommand(0x40);			  /*Set Y address (column     = 0)*/
	GLCD_voidSendCommand(0xB8);			  /*Set X address (Page       = 0)*/
}
/*======================================================================================*
 *======================================================================================*/
void GLCD_voidChooseSegment(u8 Copy_u8Segment_No)
{
	if( Copy_u8Segment_No == Left_only)
	{
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8HIGH);
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8LOW);
	}
	else if( Copy_u8Segment_No == Right_only)
	{
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8LOW);
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8HIGH);
	}
	else if( Copy_u8Segment_No == Both)
	{
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8HIGH);
		DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8HIGH);
	}
	else
	{
		// nothing
	}
}
/*======================================================================================*
 *======================================================================================*/
void GLCD_voidGoto(u8 Copy_u8Page, u8 Copy_u8Segment, u8 Copy_u8Column )
{

	switch(Copy_u8Page)
	{
	case Page_0: GLCD_voidSendCommand(0xB8); break;
	case Page_1: GLCD_voidSendCommand(0xB9); break;
	case Page_2: GLCD_voidSendCommand(0xBA); break;
	case Page_3: GLCD_voidSendCommand(0xBB); break;
	case Page_4: GLCD_voidSendCommand(0xBC); break;
	case Page_5: GLCD_voidSendCommand(0xBD); break;
	case Page_6: GLCD_voidSendCommand(0xBE); break;
	case Page_7: GLCD_voidSendCommand(0xBF); break;
	}
	GLCD_voidChooseSegment(Copy_u8Segment);
	GLCD_voidSendCommand(Copy_u8Column);

}
/*======================================================================================*
 *======================================================================================*/
void GLCD_voidSendString(u8 Page_No, const char* Copy_Str)
{
DIO_voidSetPinDirection(DIO_u8PORT_B, DIO_u8PIN_0, DIO_u8OUTPUT);

	u8 Local_Counter = 0;
	u16 Page = ( (0xB8) + Page_No );
	f32 Page_Inc = 0.5; /*every row is considered two pages one for each segment*/
	u8 Y_Address = 0;
	//GLCD_voidSendCommand(Page);
	/* begin with the left side  CS1=1 CS2 =0*/
	//DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN, DIO_u8HIGH);
	//DIO_voidSetPinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN, DIO_u8LOW);
	GLCD_voidGoto(Page_No , Left_only, 0x40);
	while(Copy_Str[Local_Counter] != '\0')
	{
		if( Y_Address >= 126 )/*126 to prevent the last character from
								displaying part in page and the other part in next page*/
		{
		    DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN);
		    DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN);
		    GLCD_voidSendCommand(0x40);
			GLCD_voidSendCommand(Page + Page_Inc);
			Page_Inc = Page_Inc + 0.5;
			Y_Address = 0;
			DIO_voidSetPinValue(DIO_u8PORT_B, DIO_u8PIN_0, DIO_u8HIGH);
		}

		for(u8 i=0 ; i < FONT_SIZE ; i++)
		{
			GLCD_voidSendData(font[(Copy_Str[Local_Counter] - 0x20)][i]);
			if( ((Y_Address + 1)%64 == 0)    )
			{
				DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN);
				DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN);
			    GLCD_voidSendCommand(0x40); //*Starts from first column in each segment*/
			    GLCD_voidSendCommand(Page + Page_Inc);
				Page_Inc = Page_Inc + 0.5;
			}

			Y_Address++;
		}
		if((Y_Address+1)%64 != 0)
		{
			GLCD_voidSendData(0);
			Y_Address++;

		}
		if((Y_Address+1)%64 == 0)

		{
			DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS1_PIN);
			DIO_u8TogglePinValue(GLCD_CTRL_PORT, GLCD_CS2_PIN);
			GLCD_voidSendCommand(Page+Page_Inc);
			Page_Inc = Page_Inc + 0.5;
		}
		Local_Counter++;
	}
	//GLCD_voidSendCommand(0x40);
	//GLCD_voidSendCommand(0xB8);
	GLCD_voidGoto(0 , Left_only, 0x40);
}
/*======================================================================================*
 *======================================================================================*/


