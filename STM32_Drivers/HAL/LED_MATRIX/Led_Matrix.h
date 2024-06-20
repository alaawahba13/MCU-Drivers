/*
 * Led_Matrix.h
 *
 *  Created on: Mar 16, 2024
 *      Author: Alaa
 */

#ifndef LED_MATRIX_LED_MATRIX_H_
#define LED_MATRIX_LED_MATRIX_H_

#include "../../MCAL/Lib/STM32_F103x6.h"
#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"

extern const uint8 display[43][8];
void Led_Matrix_init(SPI_Registers_t *SPIx,uint16 CS_PIN, GPIO_Registers_t *CS_GPIOx);
void Led_Matrix_writeByte(uint8 byte);
void Led_Matrix_write(uint8 address, uint8 data);
void Led_Matrix_writeString(char *str);




#endif /* LED_MATRIX_LED_MATRIX_H_ */
