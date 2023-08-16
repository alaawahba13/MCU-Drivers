/*
 * 4D_7seg.h
 *
 *  Created on: 16 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef FOURDIGIT_7SEG_4D_7SEG_H_
#define FOURDIGIT_7SEG_4D_7SEG_H_
#include "../../Atmega32/inc/DIO.h"

#define DECODER_PORT 		PORT_B

#define DECODER_PIN_A		PIN_0
#define DECODER_PIN_B		PIN_1
#define DECODER_PIN_C		PIN_2
#define DECODER_PIN_D		PIN_4

//PORT B
#define DIGIT_1		PIN_3
#define DIGIT_2		PIN_2
//PORT A
#define DIGIT_3		PIN_5
#define DIGIT_4		PIN_6

void SEG_4D_init();

void send_Number(uint16 Num);


#endif /* FOURDIGIT_7SEG_4D_7SEG_H_ */
