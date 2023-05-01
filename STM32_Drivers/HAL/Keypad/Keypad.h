/*
 * Keypad.h
 *
 *  Created on: 17 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef KEYPAD_DRIVER_KEYPAD_H_
#define KEYPAD_DRIVER_KEYPAD_H_

#include "GPIO.h"

//Define the PORT  connected to keypad
#define Keypad_PORT   		GPIOB


// Define the Keypad Cols & Rows pins
#define R0 					PIN_0
#define R1					PIN_1
#define R2 					PIN_3
#define R3					PIN_4
#define C0 					PIN_5
#define C1					PIN_6
#define C2 					PIN_7
#define C3					PIN_8


void Keypad_init();
char Keypad_Get_Key();

#endif /* KEYPAD_DRIVER_KEYPAD_H_ */
