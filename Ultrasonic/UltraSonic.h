/*
 * UltraSonic.h
 *
 *  Created on: May 27, 2023
 *      Author: My-Computer
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*Variable to Hold the measured Distance*/
extern  f32 Distance ;


#define _USE_LCD     	1
#define DONT_USE_LCD	0

#define US_Senor_TR_PORT		DIO_u8PORT_A
#define US_Senor_TR_PIN			DIO_u8PIN_0


void US_Sensor_VoidInit(void);
void US_Senor_VoidDistanceMeasure();
void US_Sensor_VoidTriggerPulse();



#endif /* ULTRASONIC_H_ */
