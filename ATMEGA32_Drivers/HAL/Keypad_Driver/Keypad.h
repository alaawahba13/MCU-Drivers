/*
 * Keypad.h
 *
 *  Created on: 17 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef KEYPAD_DRIVER_KEYPAD_H_
#define KEYPAD_DRIVER_KEYPAD_H_
#include <../../Atmega32/inc/DIO.h>
#include <util/delay.h>
#include "../../Library/BIT_MATH.h"

//Define the PORT , PIND & DDR register connected to keypad
#define Keypad_PORT   		PORTC
#define Keypad_DDR			DDRC
#define Keypad_PIN 			PINC

// Define the Keypad Cols & Rows pins
#define R0 					0
#define R1					1
#define R2 					2
#define R3					3
#define C0 					4
#define C1					5
#define C2 					6
#define C3					7


void Keypad_init();
char Keypad_Get_Key();

#endif /* KEYPAD_DRIVER_KEYPAD_H_ */
