/*
 * USART.h
 *
 *  Created on: 13 Feb 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_USART_H_
#define ATMEGA32_INC_USART_H_
//-----------------------------
//Includes
//-----------------------------
#include "Atmega32.h"
#include "../../Library/BIT_MATH.h"
#include "../../HAL/LCD_Driver/lcd.h"
#include "avr/interrupt.h"

/*
* ===============================================
* APIs Supported by "MCAL DIO DRIVER"
* ===============================================
*/

void USART_init(void);
void USART_send(uint8 data);
uint8 USART_recieve();

void USART_sendString(uint8 *str);
void USART_sendNumber(uint32 data);

void USART_recieveString(uint8 *Buff);
uint32 USART_recieveNumber();

uint8 USART_recievePeriodicData(uint8 *data);





#endif /* ATMEGA32_INC_USART_H_ */
