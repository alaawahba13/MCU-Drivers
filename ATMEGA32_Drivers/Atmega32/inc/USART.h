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
#include "BIT_MATH.h"
#include "lcd.h"
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
//Interrupt
void USART_sendNoBlock(uint8 data);
uint8 USART_recieveNoBlock();
void USART_TX_interrupt_Enable();
void USART_TX_interrupt_Disable();
void USART_RX_interrupt_Enable();
void USART_RX_interrupt_Disable();
void USART_send_string_Asynch(uint8 *str);




#endif /* ATMEGA32_INC_USART_H_ */
