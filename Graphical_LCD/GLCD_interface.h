/*************************************************
*  FILE  DESCRIPTION
*------------------------------------------------
*     File: GLCD_interfaces.h
*     Description: Contains interfaces with MCU
*
****************************************************/

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

#define GLCD_DATA_PORT			DIO_u8PORT_A
#define GLCD_CTRL_PORT	        DIO_u8PORT_C
#define GLCD_RS_PIN		        DIO_u8PIN_0
#define GLCD_RW_PIN		        DIO_u8PIN_1
#define GLCD_EN_PIN		        DIO_u8PIN_2
#define GLCD_CS1_PIN	        DIO_u8PIN_3
#define GLCD_CS2_PIN	        DIO_u8PIN_4
#define GLCD_RST_PIN	        DIO_u8PIN_5

#define TOTAL_PAGES		     	8
#define FONT_SIZE     5


enum Segments {Left_only = 0, Right_only = 1, Both = 2};
enum Pages    {Page_0 = 0, Page_1, Page_2, Page_3, Page_4, Page_5, Page_6, Page_7};



void GLCD_VoidInit();
void GLCD_voidClearScreen();

void GLCD_voidSendCommand(u8 Copy_u8Command);
void GLCD_voidSendData(u8 Copy_u8Data);


void GLCD_voidSendString(u8 Page_No, const char* Copy_Str);
void GLCD_voidChooseSegment(u8 Copy_u8Segment_No);
void GLCD_voidGoto(u8 Copy_u8Page, u8 Copy_u8Segment, u8 Copy_u8Column );


#endif /* GLCD_INTERFACE_H_ */
