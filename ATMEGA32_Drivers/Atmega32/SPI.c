/*
 * SPI.c
 *
 *  Created on: 22 Feb 2023
 *      Author: Alaa Wahba
 */

#include "SPI.h"

void SPI_Init() {
#ifdef MASTER_MODE
	/* GPIO pins Configuration */
	// Set MISO as input
	DIO_initPin(MISO, SPI_PORT, INPUT);
	// Set MOSI, SCK, SS as output
	DIO_initPin(MOSI, SPI_PORT, OUTPUT);
	DIO_initPin(SCLK, SPI_PORT, OUTPUT);
	DIO_initPin(SS, SPI_PORT, OUTPUT);

	/* Master Configuration */
	// Enable SPI
	// Configure it as Master
	// shift clock =clk/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
#endif

#ifdef SLAVE_MODE
	/* GPIO pins Configuration */
		// Set MISO as output
		DIO_initPin(MISO, SPI_PORT, OUTPUT);
		// Set MOSI, SCK, SS as input
		DIO_initPin(MOSI, SPI_PORT, INPUT);
		DIO_initPin(SS, SPI_PORT, INPUT);
		DIO_initPin(SCLK, SPI_PORT, INPUT);
				/* Slave Configuration */
		// Enable SPI
		SPCR = (1<<SPE);
		// Configure it as Slave
		CLEAR(SPCR, MSTR);

#endif

}
uint8 SPI_SendRecieveData(uint8 Data) {
	SPDR = Data;
	//When a serial transfer is complete, the SPIF Flag is Set.
	while (!(GET(SPSR, SPIF)));
	return SPDR;
}
