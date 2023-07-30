/*
 * I2C.h
 *
 *  Created on: 22 Jul 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_I2C_H_
#define ATMEGA32_INC_I2C_H_

#include "DIO.h"
#include "Atmega32.h"
#include "../../Library/BIT_MATH.h"

#define MASTER_Mode
// #define SLAVE_Mode


#define prescalar 		1		// Has values of 1 , 4 , 16 , 64

void I2C_init(unsigned long SCL_Clock);
void I2C_Start();
void I2C_Stop();
void I2C_Write(uint8 data);
uint8 I2C_Read();

//Slave Functions

void I2C_setAddress(uint8 address);
uint8 Slave_Read(uint8 ack);

#endif /* ATMEGA32_INC_I2C_H_ */
