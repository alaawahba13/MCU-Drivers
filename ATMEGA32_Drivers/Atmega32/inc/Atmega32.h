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
#include "../../Library/Platform_types.h"
#include <stdio.h>


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


//-------------------------------------------------------------
//		   			I2C Registers
//-------------------------------------------------------------
#define TWDR						(*(volatile uint8 *)0x23)
#define TWAR						(*(volatile uint8 *)0x22)
#define TWSR						(*(volatile uint8 *)0x21)
#define TWBR						(*(volatile uint8 *)0x20)
#define TWCR						(*(volatile uint8 *)0x56)

// I2C Control Register bits

#define TWIE		0		//  Interrupt Enable

#define TWEN		2		//  TWI Enable Bit
#define TWWC		3		// READ ONLY : Write Collision Flag
#define TWSTO		4		//  STOP Condition Bit
#define TWSTA		5		// START Condition Bit
#define TWEA		6		// Enable Acknowledge Bit
#define TWINT		7		//TWI Interrupt Flag

//-------------------------------------------------------------
//		   			Watch Dog timer Registers
//-------------------------------------------------------------
#define WDTCR						(*(volatile uint8 *)0x41)

#define WDP0		0		//  Prescalar bits
#define WDP1		1
#define WDP2		2
#define WDE			3		//  Watchdog Enable
#define WDTOE		4		//  Watchdog Turn-off Enable

//-------------------------------------------------------------
//		   			 Timer0 Registers
//-------------------------------------------------------------

#define TCCR0						(*(volatile uint8 *)0x53)
#define TCNT0						(*(volatile uint8 *)0x52)
#define OCR0						(*(volatile uint8 *)0x5C)
#define TIMSK						(*(volatile uint8 *)0x59)
#define TIFR						(*(volatile uint8 *)0x58)

// Timer/Counter Control Register


#define CS00		0		//  Clock Select
#define CS01		1
#define CS02		2
#define WGM01		3		// Waveform generation mode 1
#define COM00		4		//  Compare Match Output Mode 0
#define COM01		5
#define WGN00		6		// Waveform generation mode 0
#define FOC0		7		//Force Output Compare



// Timer/Counter Interrupt Mask  register

		//Timer 0
#define TOIE0		0		//  Output Compare Match Interrupt Enable
#define OCIE0		1		//  Overflow Interrupt Enable
		//Timer 1
#define TOIE1		2		//	Overflow Interrupt Enable
#define OCIE1B		3		// Output Compare B Match Interrupt Enable
#define OCIE1A		4		// Output Compare A Match Interrupt Enable
#define TICIE1		5		// Input Capture Interrupt Enable
		// Timer 2
#define TOIE2		6
#define OCIE2		7


// Timer/Counter Interrupt Flag  register
		// Timer 0
#define TOV0		0		//  Output Compare Match Flag 0
#define OCF0		1		//  Overflow Flag
		//Timer 1
#define TOV1		2		//  Overflow Flag
#define OCF1B		3		// Output Compare B Match Flag
#define OCF1A		4		// Output Compare B Match Flag
#define ICF1		5		//Input capture flag
		//Timer 2
#define TOV2		6
#define OCF2		7


//-------------------------------------------------------------
//		   			 Timer1 Registers
//-------------------------------------------------------------

#define TCCR1A						(*(volatile uint8 *)0x4F)
#define TCCR1B						(*(volatile uint8 *)0x4E)
#define TCNT1H						(*(volatile uint8 *)0x4D)
#define TCNT1L						(*(volatile uint8 *)0x4C)
#define OCR1AH						(*(volatile uint8 *)0x4B)
#define OCR1AL						(*(volatile uint8 *)0x4A)
#define OCR1BH						(*(volatile uint8 *)0x49)
#define OCR1BL						(*(volatile uint8 *)0x48)
#define ICR1H						(*(volatile uint8 *)0x47)
#define ICR1L						(*(volatile uint8 *)0x46)

// TCCR1A register


#define WGM10		0		//Waveform Generation Mode
#define WGM11		1
#define FOC1B		2		// Force Output Compare for Compare unit B
#define FOC1A		3		// Force Output Compare for Compare unit A
#define COM1B0		4		// Compare Output Mode for Compare unit B
#define COM1B1		5
#define COM1A0		6		//Compare Output Mode for Compare unit A
#define COM1A1		7



// TCCR1B register

#define CS10		0		// Clock Select
#define CS11		1
#define CS12		2
#define WGM12		3		//Waveform Generation Mode
#define WGM13		4

#define ICES1		6		// Input Capture Edge Select
#define ICNC1		7 		//  Input Capture Noise Canceler

//-------------------------------------------------------------
//		   			 ADC Registers
//-------------------------------------------------------------

#define ADMUX						(*(volatile uint8 *)0x27)
#define ADCSRA						(*(volatile uint8 *)0x26)
#define ADC							(*(volatile uint16 *)0x24)
#define ADCL						(*(volatile uint8 *)0x24)
#define ADCH						(*(volatile uint8 *)0x25)

// ADC Multiplexer selection register

#define MUX0		0		// Analog Channel and Gain Selection Bits
#define MUX1		1
#define MUX2		2
#define MUX3		3
#define MUX4		4
#define ADLAR		5		// ADC Left Adjust Result
#define REFS0		6		//  Reference Selection Bits
#define REFS1		7


// ADC Control and status register register

#define ADPS0		0		//ADC Prescaler Select Bits
#define ADPS1		1
#define ADPS2		2
#define ADIE		3		//  ADC Interrupt Enable
#define ADIF		4		//  ADC Interrupt Flag
#define ADATE		5		//  ADC Auto Trigger Enable
#define ADSC		6		//  ADC Start Conversion
#define ADEN		7		//  ADC Enable

//-------------------------------------------------------------
//		   			 Generic Registers
//-------------------------------------------------------------
#define SREG 						(*(volatile uint8 *)0x5F)
#define SFIOR						(*(volatile uint8 *)0x50)

//Status Register
#define I			7

// Special Function IO register

#define PSR10		0		// Prescaler Reset Timer/Counter1 and Timer/Counter0
#define PSR2		1		// Prescaler Reset Timer/Counter2
#define PUD			2		//  Pull-up Disable
#define ACME		3		// Analog Comparator Multiplexer Enable

#define ADTS0		5		//  ADC Auto Trigger Source
#define ADTS1		6
#define ADTS2		7



#endif /* ATMEGA32_INC_ATMEGA32_H_ */
