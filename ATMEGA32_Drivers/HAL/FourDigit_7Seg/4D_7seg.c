/*
 * 4D_7seg.c
 *
 *  Created on: 16 Aug 2023
 *      Author: Alaa Wahba
 */

#include "4D_7seg.h"

void SEG_4D_init() {
	DIO_initPin(DIGIT_1, PORT_A, OUTPUT);
	DIO_initPin(DIGIT_2, PORT_A, OUTPUT);
	DIO_initPin(DIGIT_3, PORT_B, OUTPUT);
	DIO_initPin(DIGIT_4, PORT_B, OUTPUT);

	DIO_WritePin(DIGIT_1, PORT_A, HIGH);
	DIO_WritePin(DIGIT_2, PORT_A, HIGH);
	DIO_WritePin(DIGIT_3, PORT_B, HIGH);
	DIO_WritePin(DIGIT_4, PORT_B, HIGH);

	DIO_initPin(DECODER_PIN_A, DECODER_PORT, OUTPUT);
	DIO_initPin(DECODER_PIN_B, DECODER_PORT, OUTPUT);
	DIO_initPin(DECODER_PIN_C, DECODER_PORT, OUTPUT);
	DIO_initPin(DECODER_PIN_D, DECODER_PORT, OUTPUT);

	DIO_WritePin(DECODER_PIN_A, DECODER_PORT, LOW);
	DIO_WritePin(DECODER_PIN_B, DECODER_PORT, LOW);
	DIO_WritePin(DECODER_PIN_C, DECODER_PORT, LOW);
	DIO_WritePin(DECODER_PIN_D, DECODER_PORT, LOW);

}
void send_Number(uint16 Num) {
	uint16 data = 0;
	if (data <= 9999) {
		// First digit 56 3 0
		DIO_WritePin(DIGIT_1, PORT_A, LOW);
		data = Num % 10;
		DIO_WritePin(DECODER_PIN_A, DECODER_PORT, GET(data, 0));
		DIO_WritePin(DECODER_PIN_B, DECODER_PORT, GET(data, 1));
		DIO_WritePin(DECODER_PIN_C, DECODER_PORT, GET(data, 2));
		DIO_WritePin(DECODER_PIN_D, DECODER_PORT, GET(data, 3));
		_delay_ms(10);
		DIO_WritePin(DIGIT_1, PORT_A, HIGH);

		// Second digit 56 3 0
		DIO_WritePin(DIGIT_2, PORT_A, LOW);
		Num /= 10;
		data = Num % 10;
		DIO_WritePin(DECODER_PIN_A, DECODER_PORT, GET(data, 0));
		DIO_WritePin(DECODER_PIN_B, DECODER_PORT, GET(data, 1));
		DIO_WritePin(DECODER_PIN_C, DECODER_PORT, GET(data, 2));
		DIO_WritePin(DECODER_PIN_D, DECODER_PORT, GET(data, 3));
		_delay_ms(10);
		DIO_WritePin(DIGIT_2, PORT_A, HIGH);

		// Third digit 56
		DIO_WritePin(DIGIT_3, PORT_B, LOW);
		Num /= 10;
		data = Num % 10;
		DIO_WritePin(DECODER_PIN_A, DECODER_PORT, GET(data, 0));
		DIO_WritePin(DECODER_PIN_B, DECODER_PORT, GET(data, 1));
		DIO_WritePin(DECODER_PIN_C, DECODER_PORT, GET(data, 2));
		DIO_WritePin(DECODER_PIN_D, DECODER_PORT, GET(data, 3));
		_delay_ms(10);
		DIO_WritePin(DIGIT_3, PORT_B, HIGH);

		// Fourth digit 56 3 0
		DIO_WritePin(DIGIT_4, PORT_B, LOW);
		Num /= 10;
		data = Num % 10;
		DIO_WritePin(DECODER_PIN_A, DECODER_PORT, GET(data, 0));
		DIO_WritePin(DECODER_PIN_B, DECODER_PORT, GET(data, 1));
		DIO_WritePin(DECODER_PIN_C, DECODER_PORT, GET(data, 2));
		DIO_WritePin(DECODER_PIN_D, DECODER_PORT, GET(data, 3));
		_delay_ms(10);
		DIO_WritePin(DIGIT_4, PORT_B, HIGH);

	}
}

