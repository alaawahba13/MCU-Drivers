/*
 * I2C.c
 *
 *  Created on: 22 Jul 2023
 *      Author: Alaa Wahba
 */

#include "inc/I2C.h"

//Master Functions
void I2C_init() {
	TWBR = (uint8) (((F_CPU / SCL_Clock) - 16) / (2 * prescalar));
	switch (prescalar) {
	case 1:
		TWSR = 0;
		break;

	case 4:
		TWSR = 1;
		break;

	case 16:
		TWSR = 2;
		break;

	case 64:
		TWSR = 3;
		break;
	}
}
void I2C_Start() {
	//Write HIgh to start bit, enable bit & clear interrupt flag in control register
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/*
	 * After a START condition has been transmitted, the TWINT Flag is set by hardware
	 *  and the status code in TWSR will be 0x08
	 */
	while (!GET(TWCR, TWINT))
		;

}

void I2C_Write(uint8 data) {

	TWDR = data;
	//After updating TWDR, the TWINT bit should be cleared (by writing it to one) to continue the transfer.
	TWCR = (1 << TWINT) | (1 << TWEN);
	// This indicates that the DATA has been transmitted, and  ACK/NACK has been received.
	while (!GET(TWCR, TWINT))
		;

}

uint8 I2C_Read(uint8 ack) {
	if (ack) {
		TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	} else {
		TWCR = (1 << TWINT) | (1 << TWEN);
	}
	while (!GET(TWCR, TWINT))
		;
	return TWDR;
}

void I2C_Stop() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	_delay_us(100);

}

//Slave Functions
void I2C_setAddress(uint8 address) {
	TWAR = address;
}

uint8 Slave_Read(uint8 ack) {
	TWCR |= (1 << TWEA) | (1 < TWINT) | (1 << TWEN);
	//After its own slave address and the write bit have been received, the TWINT Flag is se
	while (!GET(TWCR, TWINT))
		;
	/*
	 * Own SLA+W has been received;
	 ACK has been returned
	 */
	while (TWSR != 0x60)
		;
	TWCR |= (1 << TWEA) | (1 < TWINT) | (1 << TWEN);
	while (!GET(TWCR, TWINT))
		;
	while (TWSR != 0x80)
		; //Previously addressed with ownSLA+W; data has been received;	ACK has been returned
	return TWDR;
}

void I2C_SendSlaveAddress(uint8 slaveAddress, uint8 Direction) {
	I2C_Write(slaveAddress + Direction);
	if (!Direction)
		while ((TWSR) != 0x18)
			;

}
