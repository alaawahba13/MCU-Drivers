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

typedef struct{
	uint8 baudRate;   // @ref USART_BaudRate_define
	uint8 DoubleSpeed;
}UART_Config_t;


/*
 * @ref USART_BaudRate_define
 */
#define USART_BaudRate_2400						2400
#define USART_BaudRate_4800						4800
#define USART_BaudRate_9600						9600
#define USART_BaudRate_14400					14400
#define USART_BaudRate_19200					19200
#define USART_BaudRate_28800					28800
#define USART_BaudRate_38400					38400
#define USART_BaudRate_57600					57600
#define USART_BaudRate_76800					76800
#define USART_BaudRate_115200					115200
#define USART_BaudRate_230400					230400
#define USART_BaudRate_250000					250000

/*
 * @ref Double_speed
 */

#define DOUBLE_Speed_EN							8UL
#define DOUBLE_Speed_EN							16UL


/*
* ===============================================
* APIs Supported by "MCAL DIO DRIVER"
* ===============================================
*/


void USART_init(UART_Config_t *pinConfig);
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
