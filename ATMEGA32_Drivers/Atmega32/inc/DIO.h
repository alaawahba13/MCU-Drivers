/*
 * DIO.h
 *
 *  Created on: 18 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_DIO_H_
#define ATMEGA32_INC_DIO_H_
//=======================
//Includes
//=======================
#include "Atmega32.h"
#include "util/delay.h"
#include "../../Library/BIT_MATH.h"
//===============================================
//Macros Configuration References
//===============================================

/*
 * @ref pinNumber_define
 */
#define PIN_0			0
#define PIN_1			1
#define PIN_2			2
#define PIN_3			3
#define PIN_4			4
#define PIN_5			5
#define PIN_6			6
#define PIN_7			7
/*
 * @ref port_define
 */

#define PORT_A			(uint8)0
#define PORT_B			(uint8)1
#define PORT_C			(uint8)2
#define PORT_D			(uint8)3

/*
 * @ref pinDirection_define
 */
#define OUTPUT 			1
#define INPUT 			0
/*
 * @ref portDirection_define
 */
#define PORT_OUTPUT 			0xFF
#define PORT_INPUT 				0x00

/*
 * @ref value_define
 */

#define HIGH	 		1
#define LOW				0

/*
 * @ref port_value_define
 */

#define PORT_HIGH	 		0xFF
#define PORT_LOW			0x00

/*
* ===============================================
* APIs Supported by "MCAL DIO DRIVER"
* ===============================================
*/

void DIO_initPin(uint8 pinNumber , uint8 port ,uint8 pinDirection );
void DIO_initPort( uint8 port ,uint8 portDirection );

void DIO_WritePin(uint8 pinNumber , uint8 port ,uint8 value);
void DIO_WritePort(uint8 port ,uint8 value);

uint8 DIO_ReadPin(uint8 pinNumber , uint8 port);
uint8 DIO_ReadPort(uint8 port);

void DIO_Toggle(uint8 pinNumber , uint8 port);

#endif /* ATMEGA32_INC_DIO_H_ */
