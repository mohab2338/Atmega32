/*
 * KPAD.h
 *
 *  Created on: Dec 16, 2022
 *      Author: My-Computer
 */

#ifndef KPAD_H_
#define KPAD_H_

#define KPAD_PORT		DIO_u8PORT_A
#define SUCCSSES			1

u8 KPAD_Init();
u16 KPAD_Read();

#endif /* KPAD_H_ */
