/*
 * SPI.h
 *
 *  Created on: 22 Feb 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_SPI_H_
#define ATMEGA32_INC_SPI_H_

#include "DIO.h"
#include "Atmega32.h"
#include "../../Library/BIT_MATH.h"
#define MASTER_MODE
// #define SLAVE_MODE

#define SPI_PORT			PORT_B
#define MOSI 				PIN_5
#define MISO 				PIN_6
#define SCLK 				PIN_7
#define SS	 				PIN_4


void SPI_Init();
uint8 SPI_SlendRecieveData(uint8 Data);



#endif /* ATMEGA32_INC_SPI_H_ */
