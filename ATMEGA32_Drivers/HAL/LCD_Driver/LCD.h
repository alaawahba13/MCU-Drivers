/*
 * LCD.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef LCD_H_
#define LCD_H_
#include "../../Atmega32/inc/DIO.h"
#include <util/delay.h>
#include "../../Library/BIT_MATH.h"
#include "string.h"

/*This is used for lcd data pins D0-D7 */
#define LCD_PORT 				PORTB
#define LCD_DDR  				DDRB


#define D4 						PIN_0
#define D5 						PIN_1
#define D6 						PIN_2
#define D7 						PIN_4


/* This is used for three control pins RS, RW, Enable */
#define LCD_CONTROL_PORT 		PORTA
#define LCD_CONTROL_DDR  		DDRA
// define the three control pins connected to MCU
#define ENABLE_SWITCH			2
#define REGISTER_SELECT         3

//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_4x20
//#define LCD_2x16

#define MAX_COLS				20
#define MAX_ROWS				4

#define DATA_SHIFT 				0
/* Some instructions from data sheet */
#define CURSOR_FIRST_LINE 		(0x80)
#define CURSOR_SECOND_LINE 		(0xC0)
#define CURSOR_THIRD_LINE 		(0x94)
#define CURSOR_FOURTH_LINE 		(0xD4)

#define FUNCTION_8BIT_2LINES 	(0x38)
#define FUNCTION_4BIT_2LINES 	(0x28)

#define SHIFT_DISPLAY_LEFT 		(0x18)
#define SHIFT_DISPLAY_RIGHT 	(0x1C)

#define MOVE_CURSOR_LEFT 		(0x10)
#define MOVE_CURSOR_RIGHT 		(0x14)
#define DISPLAY_OFF				(0x08)
#define DISPLAY_ON_CURSOR_OFF	(0x0C)
#define DISPLAY_ON_CURSOR_ON	(0x0E)
#define DISPLAY_ON_CURSOR_BLINK	(0x0F)

#define ENTRY_MODE 				(0x06)
#define ENTRY_DEC 				(0x04)
#define ENTRY_DEC_SHIFT			(0x05)
#define ENTRY_INC 				(0x06)
#define ENTRY_INC_SHIFT			(0x07)

#define CLEAR_SCREEN 			(0x01)

void isBusy(void);
void lcd_kick(void);
void lcd_Send_Command(unsigned char command);
void lcd_Send_Char(unsigned char data);
void lcd_send_String(char *string);
void lcd_init(void);
void lcd_Clear_Screen(void);
void lcd_GOTO_XY(unsigned char row , unsigned char col);
void lcd_display_number(int Number);
void lcd_display_Real_number(double Number);
void LCD_createCustomCharacter(uint8 *pattern, uint8 location);

#endif /* LCD_H_ */
