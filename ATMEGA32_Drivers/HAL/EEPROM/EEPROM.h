/*
 * EEPROM.h
 *
 *  Created on: 23 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

#include "../../Atmega32/inc/I2C.h"
#define EEPROM_SlaveAddress 		(uint8)0xA0

#define EEPROM_MAX_PAGES			16
#define EEPROM_MAX_BYTES			16


void EEPROM_init();
void EEPROM_Write(uint8 *data, uint16 address,uint8 nBytes);
void EEPROM_Read(uint8 *data, uint16 address,uint32 nBytes);

#endif /* EEPROM_EEPROM_H_ */
