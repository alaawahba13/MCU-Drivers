/*
 * USART.c
 *
 *  Created on: 13 Feb 2023
 *      Author: Alaa Wahba
 */

#include "inc/USART.h"
#define Default_Stop 		'\r'
static uint32 flag = 1;
static uint8 *TX_str;

void USART_init(UART_Config_t *pinConfig) {
	/*   Baud rate   */
	uint16 ubrr_value = (uint16) (((F_CPU / (pinConfig->baudRate * pinConfig->DoubleSpeed))) - 1);

	UBRRH = ubrr_value >> 8;
	UBRRL = ubrr_value;

	/*  FRAME 	  */
	//This bit selects  Asynchronous
	CLEAR(UCSRC, UMSEL);
	//These bits enable and set type of parity generation (No parity )
	CLEAR(UCSRC, UPM0);
	CLEAR(UCSRC, UPM1);
	//This bit selects the number of Stop Bits to be inserted by the Transmitter (1 bit)
	CLEAR(UCSRC, USBS);
	// sets the number of data bits (8 bits by default)
	CLEAR(UCSRB, UCSZ2);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	/*   Enable  */
	SET(UCSRB, RXEN);	//Writing this bit to one enables The USART Receiver.
	SET(UCSRB, TXEN);	//Writing this bit to one enables The USART Transmitter.

}

void USART_send(uint8 data) {
	//The transmit buffer can only be written when the UDRE Flag in the UCSRA Register is set.
	while (!GET(UCSRA, UDRE))
		;
	UDR = data;

}
uint8 USART_recieve() {
	/*
	 * This flag bit is set when there are unread data in the receive buffer
	 * and cleared when the receive buffer is empty
	 */
	while (!GET(UCSRA, RXC))
		;
	return UDR;

}

void USART_sendNumber(uint32 data) {

	char str[7];

	sprintf(str, "%d", data);  // Adjust the formatting to your liking.

	USART_sendString(str);

}
uint32 USART_recieveNumber() {
	uint32 num;
	/* uint8 *p = (uint8 *)&num;
	 p[0] = USART_recieve();
	 p[1] = USART_recieve();
	 p[2] = USART_recieve();
	 p[3] = USART_recieve();*/
	return num;
}
void USART_sendString(uint8 *str) {
	for (uint8 i = 0; i < str[i]; i++)
		USART_send(str[i]);

	USART_send(Default_Stop);
}

void USART_recieveString(uint8 *Buff) {

	uint8 i = 0;
	Buff[i] = USART_recieve();
	while (Buff[i] != Default_Stop) {
		i++;
		Buff[i] = USART_recieve();
	}
	Buff[i] = '\0';
}

uint8 USART_recievePeriodicData(uint8 *data) {
	if (GET(UCSRA, RXC)) { // No blocking
		*data = UDR;
		return 1; 	//As an indication that there's sent data
	}
	return 0; 			// When no data is sent
}

//Interrupt

// Doesn't check if data is sent or not
void USART_sendNoBlock(uint8 data) {
	UDR = data;
}
uint8 USART_recieveNoBlock() {
	return UDR;
}
void USART_TX_interrupt_Enable() {
	SET(UCSRB, TXCIE);
}
void USART_TX_interrupt_Disable() {
	CLEAR(UCSRB, TXCIE);
}

void USART_RX_interrupt_Enable() {
	SET(UCSRB, RXCIE);
}
void USART_RX_interrupt_Disable() {
	CLEAR(UCSRB, RXCIE);

}
void USART_send_string_Asynch(uint8 *str) {
	if (flag == 1) {
		USART_sendNoBlock(str[0]);
		TX_str = str;
		flag = 0;
		USART_TX_interrupt_Enable();

	}
}

void __vector_15(void) __attribute__ ((signal));
void __vector_15(void) {
	static uint8 i = 1;
	if (TX_str[i] != '\0') {
		USART_sendNoBlock(TX_str[i]);
		i++;

	} else {
		i = 1;
		flag = 1; // Flag is set to one when transmit is complete.
		//	USART_TX_interrupt_Disable();

	}
}
