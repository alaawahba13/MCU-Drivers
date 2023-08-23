/*
 * EEPROM.c
 *
 *  Created on: 22 Aug 2023
 *      Author: Alaa Wahba
 */

//=======================
//       Includes
//=======================
#include "EEPROM.h"

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void EEPROM_init() {
	I2C_pinConfig_t I2C_pinConfig;
	I2C_pinConfig.Clock_Speed = I2C_CLK_SM_100K;
	I2C_pinConfig.I2C_Mode = I2C_Mode_I2C;
	I2C_pinConfig.Stretch_Mode = I2C_Stretch_EN;
	I2C_pinConfig.ACK_Enable = I2C_ACK_EN;
	I2C_pinConfig.P_Slave_CallBack_Fun = NULL;

	I2C_init(&I2C_pinConfig, I2Cx_EEPROM);
	I2C_GPIO_SetPins(I2Cx_EEPROM);

}
uint8 EEPROM_Write(uint8 *data, uint32 dataLen, uint32 MemoryAddress) {
	uint8 i;
	uint8 buffer[256];
	buffer[0] = (uint8) (MemoryAddress >> 8);
	buffer[1] = (uint8) (MemoryAddress);
	for (i = 2; i < (dataLen + 2); i++)
		buffer[i] = data[i - 2];

	I2C_Master_TX(I2Cx_EEPROM, EEPROM_SlaveAddress, buffer, (dataLen + 2), STOP,
			NO_REPEATED_START);
	return 0;
}
uint8 EEPROM_Read(uint8 *data, uint32 dataLen, uint32 MemoryAddress) {
	uint8 buffer[256];
	buffer[0] = (uint8) (MemoryAddress >> 8);
	buffer[1] = (uint8) (MemoryAddress);
	I2C_Master_TX(I2Cx_EEPROM, EEPROM_SlaveAddress, buffer, 2, NO_STOP,
			NO_REPEATED_START);
I2C_Master_RX(I2Cx_EEPROM, EEPROM_SlaveAddress, data, dataLen , STOP,
			REPEATED_START);
	return 0;

}
