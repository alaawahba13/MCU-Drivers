/*
 * Keypad.c
 *
 *  Created on: 17 Jan 2023
 *      Author: Alaa Wahba
 */


#include "Keypad.h"

int Keypad_Cols[] = {C0 ,C1,C2,C3};
int Keypad_Rows[] = {R0 ,R1,R2,R3};
void Keypad_init(){
	/*
	 * The columns are output which are used to scan the buttons by writing GND
	 *		to each column sequentially.
	 * The rows are input so if the button is pressed it's connected to GND
	 *
	 */
	Keypad_COL_DDR |= ( (1<<C0) | (1<<C1) |(1<<C2) |(1<<C3) );
	Keypad_ROW_DDR &= ~((1<<R0) | (1<<R1) |(1<<R2) |(1<<R3) );
	/*
	 * Initialize the PORT to 1 so the Cols are connected VCC
	 * while the ROWs are input_pullup
	 */
	Keypad_Row_PORT |= ((1<<R0) | (1<<R1) |(1<<R2) |(1<<R3) );
	Keypad_COL_PORT = 0xff;
}
char Keypad_Get_Key(){

	int i, j;
	char ret_key = 'A';
	for(i =0 ; i< 4 ; i++){  // Rows loop
		Keypad_COL_PORT |= ((1<<Keypad_Cols[0]) | (1<<Keypad_Cols[1]) | (1<<Keypad_Cols[2]) | (1<<Keypad_Cols[3]));
		Keypad_COL_PORT &= ~(1<<Keypad_Cols[i]);
		for(j =0 ; j< 4 ; j++){ // colws loop
			if(!GET(Keypad_ROW_PIN, Keypad_Rows[j]))
			{
				while(!GET(Keypad_ROW_PIN, Keypad_Rows[j])); // single press
					ret_key = arr_keys[j][i];
				}

			}
		}
	return ret_key;
}
