/*
 * Keypad.c
 *
 *  Created on: 17 Jan 2023
 *      Author: Alaa Wahba
 */

#include "Keypad.h"

int Keypad_Cols[] = { C0, C1, C2, C3 };
int Keypad_Rows[] = { R0, R1, R2, R3 };
void Keypad_init() {
	/*
	 * The columns are output which are used to scan the buttons by writing GND
	 *		to each column sequentially.
	 * The rows are input so if the button is pressed it's connected to GND
	 *
	 */
	GPIO_PinConfig_t pinConfig;
	for (int i = 0; i < 4; i++) {
		pinConfig.MODE = MODE_OUTPUT_PP;
		pinConfig.Output_Speed = SPEED_10M;
		pinConfig.Pin_Number = Keypad_Cols[i];
		GPIO_init(Keypad_COL_PORT, &pinConfig);
	}
	for (int i = 0; i < 4; i++) {
		pinConfig.MODE = MODE_OUTPUT_PP;
		pinConfig.Output_Speed = SPEED_10M;
		pinConfig.Pin_Number = Keypad_Rows[i];
		GPIO_init(Keypad_Row_PORT, &pinConfig);
	}
	/*
	 * Initialize the PORT to 1 so the Cols are connected VCC
	 * while the ROWs are input_pullup
	 */
	for (int i = 0; i < 4; i++) {
		GPIO_WritePin(Keypad_Row_PORT, Keypad_Rows[i],PIN_HIGH);
		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[i],PIN_HIGH);
	}
}
char Keypad_Get_Key() {

	int i, j;
	char ret_key = 'A';
	for (i = 0; i < 4; i++) {  // Rows loop

		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[0], PIN_HIGH);
		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[1], PIN_HIGH);
		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[2], PIN_HIGH);
		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[3], PIN_HIGH);
		GPIO_WritePin(Keypad_COL_PORT, Keypad_Cols[i], PIN_LOW);
		for (j = 0; j < 4; j++) { // cols loop
			if (!GPIO_ReadPin(Keypad_Row_PORT, Keypad_Rows[j])) {
				while (!GPIO_ReadPin(Keypad_Row_PORT, Keypad_Rows[j]))
					; // single press
				ret_key = arr_keys[j][i];

			}

		}
	}
	return ret_key;
}

