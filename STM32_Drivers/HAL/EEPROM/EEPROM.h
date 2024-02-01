/*
 * EEPROM.h
 *
 *  Created on: 22 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

//=======================
//       Includes
//=======================
#include "../../MCAL/I2C/I2C.h"

//===============================================
//      Macros Configuration
//===============================================

#define EEPROM_SlaveAddress 		0x2A
#define I2Cx_EEPROM					I2C1

/*
* ===============================================
*      APIs Supported by "HAL EEPROM DRIVER"
* ===============================================
*/
void EEPROM_init();
uint8 EEPROM_Write(uint8 *data , uint32 dataLen, uint32 MemoryAddress);
uint8 EEPROM_Read(uint8 *data , uint32 dataLen, uint32 MemoryAddress);

#endif /* INC_EEPROM_H_ */
