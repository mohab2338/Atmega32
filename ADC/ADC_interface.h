/*
 * ADC_interface.h
 *
 *  Created on: Mar 17, 2022
 *      Author: MyComputer
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
//*reference voltage choices*//
#define EXTERNAL_VCC_CAP		0
#define INTERNAL_VREF_OFF		1
#define INT256_CAP_ON_ARFF		2
/*Prescaler choices*/
#define PRESCALER_2				0
#define PRESCALER_4				1
#define PRESCALER_8				2
#define PRESCALER_16			3
#define PRESCALER_32			4
#define PRESCALER_64			5
#define PRESCALER_128			6
/*Right or left adjustment of data*/
#define RIGHT_ADJUST			0
#define LEFT_ADJUST				1
//*Channels*//
#define CHANNEL_0		0
#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4  		4
#define CHANNEL_5 		5
#define CHANNEL_6 	    6
#define CHANNEL_7 		7
//*functions*//
void ADC_Init();
u16 ADC_ReadChannel(u8 Copy_Channel);

#endif /* ADC_INTERFACE_H_ */
