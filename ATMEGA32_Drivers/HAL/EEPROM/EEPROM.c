/*
 * EEPROM.c
 *
 *  Created on: 23 Aug 2023
 *      Author: Alaa Wahba
 */

#include "EEPROM.h"

void EEPROM_init() {
	_delay_ms(500);
	I2C_init();
}
void EEPROM_Write(uint8 *data, uint16 address, uint8 nBytes) {
	I2C_Start();
	I2C_Write((uint8)(EEPROM_SlaveAddress | ((address & 0x0700)>>7)));
	I2C_Write((uint8)address);
	if (nBytes <= EEPROM_MAX_BYTES) {
		for (uint32 i = 0; i < nBytes; i++) {
			I2C_Write(data[i]);
		}
	}
	I2C_Stop();
}
void EEPROM_Read(uint8 *data, uint16 address, uint32 nBytes) {
	I2C_Start();
	I2C_Write((uint8)(EEPROM_SlaveAddress | ((address & 0x0700)>>7)));
	I2C_Write((uint8)address);
	I2C_Start();
	I2C_Write((uint8)(EEPROM_SlaveAddress | ((address & 0x0700)>>7) | 1));
	for (uint32 i = 0; i < nBytes; i++) {
		if (i == (nBytes - 1)){
			data[i] = I2C_Read(0);
		}else
			data[i] = I2C_Read(1);
	}

	I2C_Stop();

}
void EEPROM_Erase() {
	 const uint8_t eraseData[EEPROM_MAX_BYTES] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	  uint8 bytes = 0;

for(int i = 0 ; i <EEPROM_MAX_PAGES ; i++)
	  {
	    EEPROM_Write((uint8_t*)eraseData, bytes,EEPROM_MAX_BYTES) ;
	    _delay_ms(10);
	    bytes +=EEPROM_MAX_PAGES;
	  }
}
