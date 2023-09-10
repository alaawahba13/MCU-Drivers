/*
 * LCD.c
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#include "LCD.h"

void lcd_init() {
	// you must wait for the hardware to initialize
	_delay_ms(20);
	// set port as ouput to write commands
	SET(LCD_DDR, D4);
	SET(LCD_DDR, D5);
	SET(LCD_DDR, D6);
	SET(LCD_DDR, D7);

	// set three control pins as output and write 0
	LCD_CONTROL_DDR |= (1 << ENABLE_SWITCH | 1 << REGISTER_SELECT);
	LCD_CONTROL_PORT &= ~(1 << ENABLE_SWITCH | 1 << REGISTER_SELECT);
	_delay_ms(2);
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
	lcd_Clear_Screen();

}
void lcd_Send_Command(unsigned char command) {

#ifdef EIGHT_BIT_MODE

	// 1.Write
	LCD_PORT = command;
	// 2.Reset
	LCD_CONTROL_PORT &= ~ (1<< REGISTER_SELECT);
	// 3. Reactivate Enable
	lcd_kick();
#endif
#ifdef FOUR_BIT_MODE

	//LCD_PORT =  (command & 0xF0);
	GET(command,7) ? SET(LCD_PORT, D7) : CLEAR(LCD_PORT, D7);
	GET(command,6) ? SET(LCD_PORT, D6) : CLEAR(LCD_PORT, D6);
	GET(command,5) ? SET(LCD_PORT, D5) : CLEAR(LCD_PORT, D5);
	GET(command,4) ? SET(LCD_PORT, D4) : CLEAR(LCD_PORT, D4);

	LCD_CONTROL_PORT &= ~(1 << REGISTER_SELECT);
	lcd_kick();

	GET(command,3) ? SET(LCD_PORT, D7) : CLEAR(LCD_PORT, D7);
	GET(command,2) ? SET(LCD_PORT, D6) : CLEAR(LCD_PORT, D6);
	GET(command,1) ? SET(LCD_PORT, D5) : CLEAR(LCD_PORT, D5);
	GET(command,0) ? SET(LCD_PORT, D4) : CLEAR(LCD_PORT, D4);

	LCD_CONTROL_PORT &= ~(1 << REGISTER_SELECT);
	lcd_kick();
#endif

}
void lcd_Send_Char(unsigned char character) {

#ifdef EIGHT_BIT_MODE

	//1. set the RS to 1 to send data
	LCD_CONTROL_PORT |= (1<< REGISTER_SELECT);
	//2. Write data
	LCD_PORT = character;
	// Reactivate Enable
	lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	GET(character,7) ? SET(LCD_PORT, D7) : CLEAR(LCD_PORT, D7);
	GET(character,6) ? SET(LCD_PORT, D6) : CLEAR(LCD_PORT, D6);
	GET(character,5) ? SET(LCD_PORT, D5) : CLEAR(LCD_PORT, D5);
	GET(character,4) ? SET(LCD_PORT, D4) : CLEAR(LCD_PORT, D4);
	LCD_CONTROL_PORT |= (1 << REGISTER_SELECT);

	lcd_kick();
	GET(character,3) ? SET(LCD_PORT, D7) : CLEAR(LCD_PORT, D7);
	GET(character,2) ? SET(LCD_PORT, D6) : CLEAR(LCD_PORT, D6);
	GET(character,1) ? SET(LCD_PORT, D5) : CLEAR(LCD_PORT, D5);
	GET(character,0) ? SET(LCD_PORT, D4) : CLEAR(LCD_PORT, D4);
	LCD_CONTROL_PORT |= (1 << REGISTER_SELECT);

	lcd_kick();
#endif
}
void lcd_send_String(char *string) {
	// keeps track of chars count
	int count = 0;
	while (*string > 0) {
		count++;
		lcd_Send_Char(*string++);
		// if first line is full go to second
		if (count == MAX_COLS) {
			lcd_GOTO_XY(1, 0);
		}
#ifdef LCD_4x20
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
#ifdef LCD_4x20
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

	int Frac = tmpFrac * 10000;

	sprintf(str, "%s%d.%04d", tmpSign, tmpVal, Frac);
	lcd_send_String(str);

}
void lcd_kick() {
// Enable =0 >> LCD Busy
	CLEAR(LCD_CONTROL_PORT, ENABLE_SWITCH);
	_delay_ms(6);
	SET(LCD_CONTROL_PORT, ENABLE_SWITCH);
}

void LCD_createCustomCharacter(uint8 *pattern, uint8 location) {
	uint8 i = 0;

	lcd_Send_Command(0x40 + (location * 8)); /* Send the Address of CGRAM */

	for (i = 0; i < 8; i++) {
		lcd_Send_Char(pattern[i]); /* Pass the Bytes of pattern on LCD */
	}
}
