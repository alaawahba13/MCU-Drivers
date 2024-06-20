/*
 * LCD.c
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#include "LCD.h"
GPIO_PinConfig_t pinConfig;
static int count = 0;

void isBusy(void) {
	/* 1.Set the data port as input
	 * 2.Set RW = 1 to read && Command mode >> RS =0
	 * 3.Deactivate and Activate Enable
	 */
	// STEP ONE
	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_0;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_1;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_2;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_3;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_4;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_5;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_6;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_INPUT_FLO;
	pinConfig.Pin_Number = PIN_7;
	GPIO_init(LCD_PORT, &pinConfig);
	// STEP TWO
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_LOW);
	// STEP THREE
	lcd_kick();
}

void lcd_init() {

	/*
	 * 1.delay
	 * 2. Configure port DATA as OUTPUT
	 * 3. Configure port CONTROL as OUTPUT
	 * 4. Reset all control pins.
	 * 5. delay
	 * 6. Clear Screen
	 * 7. Send command 8BIT or 4BIT
	 * 8. Go to Entry Mode
	 */

	// you must wait for the hardware to initialize
	STK_init();

	STK_delayMs(20);
	// set port as ouput to write commands
#ifdef EIGHT_BIT_MODE
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	pinConfig.Pin_Number = D0;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	pinConfig.Pin_Number = D1;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.Pin_Number = D2;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.Pin_Number = D3;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);
#endif

	pinConfig.Pin_Number = D4;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.Pin_Number = D5;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.Pin_Number = D6;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);

	pinConfig.Pin_Number = D7;
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_PORT, &pinConfig);

	// set three control pins as output and write 0
	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Pin_Number = ENABLE_SWITCH;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_CONTROL_PORT, &pinConfig);
	GPIO_WritePin(LCD_CONTROL_PORT, ENABLE_SWITCH, PIN_LOW);

	pinConfig.MODE = MODE_OUTPUT_PP;
	pinConfig.Pin_Number = REGISTER_SELECT;
	pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(LCD_CONTROL_PORT, &pinConfig);
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_LOW);

	STK_delayMs(15);
	lcd_Clear_Screen();
	/* Define the lcd Mode by its instruction*/
#ifdef EIGHT_BIT_MODE
	lcd_Send_Command(FUNCTION_8BIT_2LINES);
#endif
#ifdef FOUR_BIT_MODE
	// Command that initializes LCD as four bit mode
	lcd_Send_Command(0x02);
	lcd_Send_Command(FUNCTION_4BIT_2LINES);
#endif
	lcd_Send_Command(ENTRY_MODE);
	lcd_Send_Command(CURSOR_FIRST_LINE);
	lcd_Send_Command(DISPLAY_ON_CURSOR_BLINK);

}
void lcd_Send_Command(unsigned char command) {
	/*
	 * 1.Write command to port
	 * 2.Reset control pins
	 * 3.Deactivate and Activate Enable
	 */
#ifdef EIGHT_BIT_MODE
	GPIO_WritePort(LCD_PORT, command);
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_LOW);
	STK_delayMs(01);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_LOW);

	GPIO_WritePin(LCD_PORT, D4, GET(command, 4));
	GPIO_WritePin(LCD_PORT, D5, GET(command, 5));
	GPIO_WritePin(LCD_PORT, D6, GET(command, 6));
	GPIO_WritePin(LCD_PORT, D7, GET(command, 7));

	STK_delayMs(10);
	lcd_kick();

	GPIO_WritePin(LCD_PORT, D4, GET(command, 0));
	GPIO_WritePin(LCD_PORT, D5, GET(command, 1));
	GPIO_WritePin(LCD_PORT, D6, GET(command, 2));
	GPIO_WritePin(LCD_PORT, D7, GET(command, 3));

	STK_delayMs(10);
	lcd_kick();
#endif
}
void lcd_Send_Char(unsigned char character) {

#ifdef EIGHT_BIT_MODE
	/*
	 *1. set the RS to 1 to send data
	 *2. Write data
	 *3. Reactivate Enable
	 */
	GPIO_WritePort(LCD_PORT, character);
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_HIGH);

	STK_delayMs(10);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	GPIO_WritePin(LCD_CONTROL_PORT, REGISTER_SELECT, PIN_HIGH);

	GPIO_WritePin(LCD_PORT, D4, GET(character, 4));
	GPIO_WritePin(LCD_PORT, D5, GET(character, 5));
	GPIO_WritePin(LCD_PORT, D6, GET(character, 6));
	GPIO_WritePin(LCD_PORT, D7, GET(character, 7));
	STK_delayMs(10);
	lcd_kick();
	GPIO_WritePin(LCD_PORT, D4, GET(character, 0));
	GPIO_WritePin(LCD_PORT, D5, GET(character, 1));
	GPIO_WritePin(LCD_PORT, D6, GET(character, 2));
	GPIO_WritePin(LCD_PORT, D7, GET(character, 3));
	STK_delayMs(10);
	lcd_kick();
#endif

	if (count == MAX_COLS) {
		lcd_GOTO_XY(1, 0);
	}
#if (LCD_4x20 || LCD_4x16)
	if (count == MAX_COLS * 2) {
		lcd_GOTO_XY(2, 0);
	} else if (count == MAX_COLS * 3) {
		lcd_GOTO_XY(3, 0);
	}
#endif

	// if both lines are full clear and start over.
	else if (count == (MAX_COLS * MAX_ROWS)) {
		lcd_Clear_Screen();
		lcd_GOTO_XY(0, 0);
		count = 0;
	}

	count++;
}
void lcd_send_String(char *string) {
	while (*string > 0) {
		count++;
		lcd_Send_Char(*string++);

	}
}
void lcd_GOTO_XY(unsigned char row, unsigned char col) {

	if (row == 0) {
		if ((col < MAX_COLS) && (col >= 0))
			lcd_Send_Command(CURSOR_FIRST_LINE + col);
	} else if (row == 1) {
		if ((col < MAX_COLS) && (col >= 0))
			lcd_Send_Command(CURSOR_SECOND_LINE + col);
	}
#if (LCD_4x20 || LCD_4x16)
	else if (row == 2) {
		if ((col < MAX_COLS) && (col >= 0))
			lcd_Send_Command(CURSOR_THIRD_LINE + col);
	} else if (row == 3) {
		if ((col < MAX_COLS) && (col >= 0))
			lcd_Send_Command(CURSOR_FOURTH_LINE + col);
	}
#endif
}
void lcd_Clear_Screen(void) {
	lcd_Send_Command(CLEAR_SCREEN);
	count = 0;
}
void lcd_display_number(int Number) {
	char str[7];
	// Converts Int to String
	sprintf(str, "%d", Number);
	lcd_send_String(str);
}
void lcd_display_Real_number(double Number) {
	char str[16];
	char *tmpSign = (Number > 0) ? "" : "-";
	float tmpNum = (Number > 0) ? Number : -Number;

	int tmpVal = tmpNum;
	float tmpFrac = tmpNum - tmpVal;

	int Frac = tmpFrac * 100;

	sprintf(str, "%s%d.%02d", tmpSign, tmpVal, Frac);
	lcd_send_String(str);

}
void lcd_kick() {
	// Enable =0 >> LCD Busy
	GPIO_WritePin(LCD_CONTROL_PORT, ENABLE_SWITCH, PIN_HIGH);
	STK_delayMs(50);
	GPIO_WritePin(LCD_CONTROL_PORT, ENABLE_SWITCH, PIN_LOW);
}

void LCD_createCustomCharacter(uint8 *pattern, uint8 location) {
	uint8 i = 0;

	lcd_Send_Command(0x40 + (location * 8)); /* Send the Address of CGRAM */

	for (i = 0; i < 8; i++) {
		lcd_Send_Char(pattern[i]); /* Pass the Bytes of pattern on LCD */
	}
}

