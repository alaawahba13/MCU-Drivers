/*
 * Atmega32.h
 *
 *  Created on: 18 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_ATMEGA32_H_
#define ATMEGA32_INC_ATMEGA32_H_
//-----------------------------
//Includes
#include "Platform_types.h"

//------------------------------------------------------------
//					   	GPIO Registers
//------------------------------------------------------------

#define PORTA						(*(volatile uint8 *)0x3B)
#define DDRA						(*(volatile uint8 *)0x3A)
#define PINA						(*(volatile uint8 *)0x39)

#define PORTB						(*(volatile uint8 *)0x38)
#define DDRB						(*(volatile uint8 *)0x37)
#define PINB						(*(volatile uint8 *)0x36)

#define PORTC						(*(volatile uint8 *)0x35)
#define DDRC						(*(volatile uint8 *)0x34)
#define PINC						(*(volatile uint8 *)0x33)

#define PORTD						(*(volatile uint8 *)0x32)
#define DDRD						(*(volatile uint8 *)0x31)
#define PIND						(*(volatile uint8 *)0x30)


//-------------------------------------------------------------
//		   		External Interrupt Registers
//-------------------------------------------------------------

#define MCUCR						(*(volatile uint8 *)0x55)
#define MCUCSR						(*(volatile uint8 *)0x54)
#define GICR						(*(volatile uint8 *)0x5B)
#define GIFR						(*(volatile uint8 *)0x5A)


//-------------------------------------------------------------
//		   			USART Registers
//-------------------------------------------------------------

#define UDR							(*(volatile uint8 *)0x2C)
#define UCSRA						(*(volatile uint8 *)0x2B)
#define UCSRB						(*(volatile uint8 *)0x2A)
#define UCSRC						(*(volatile uint8 *)0x40)
#define UBRRH						(*(volatile uint8 *)0x40)
#define UBRRL						(*(volatile uint8 *)0x29)

// USART Control and Status Register A
#define MPCM		0		//Multi-processor Communication Mode
#define U2X			1		// Double the USART Transmission Speed
#define PE			2		// Parity Error
#define DOR			3		// Data overrun
#define FE			4		// Frame Error
#define UDRE		5		// Data Register Empty
#define TXC			6		// Transmit Complete
#define RXC			7		//Recieve Complete
// USART Control and Status Register B
#define TXB8		0
#define RXB8		1
#define UCSZ2		2		//Character Size
#define TXEN		3
#define RXEN		4
#define UDRIE		5
#define TXCIE		6		//Interrupt Enable
#define RXCIE		7		//Interrupt Enable
// USART Control and Status Register C
#define UCPOL		0		//Clock Polarity
#define UCSZ0		1		//Character Size
#define UCSZ1		2
#define USBS		3		//Stop Bit Select
#define UPM0		4		//Parity Mode
#define UPM1		5
#define UMSEL		6		// Mode Select
#define URSEL		7		// Register Select


//-------------------------------------------------------------
//		   			SPI Registers
//-------------------------------------------------------------

#define SPDR						(*(volatile uint8 *)0x2F)
#define SPSR						(*(volatile uint8 *)0x2E)
#define SPCR						(*(volatile uint8 *)0x2D)

// SPI Control register
#define SPR0		0		// SPI Clock rate select
#define SPR1		1
#define CPHA		2		// Clock phase
#define CPOL		3		// Clock polarity
#define MSTR		4		// Master / Slave select
#define DORD		5		// Data order
#define SPE			6		// SPI enable
#define SPIE		7		// Interrupt enable

//SPI Status Register
#define SPIF 		7		// SPI interrupt flag
#define WCOL 		6		// Write collision flag
#define SPI2X		0		// Double SPI speed

//-------------------------------------------------------------
//		   			SPI Registers
//-------------------------------------------------------------
#define USART_TXC 	16

#endif /* ATMEGA32_INC_ATMEGA32_H_ */
