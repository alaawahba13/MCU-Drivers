/*
 * LCD.h
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_
#include "../../MCAL/I2C/I2C.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"

#define SLAVE_ADDRESS_LCD 		0x4e



/* Some instructions from data sheet */
#define CURSOR_FIRST_LINE 		(0x80)
#define CURSOR_SECOND_LINE 		(0xC0)

#define CURSOR_THIRD_LINE_20 	(0x94)
#define CURSOR_FOURTH_LINE_20 	(0xD4)

#define CURSOR_THIRD_LINE_16 	(0x90)
#define CURSOR_FOURTH_LINE_16 	(0xD0)

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


void lcd_I2C_Send_Command( char cmd);
void lcd_I2C_Send_Char( char data);
void lcd_I2C_send_String(char *string);
void lcd_I2C_init(int cols, int rows, I2C_Registers_t *I2Cx);
void lcd_I2C_Clear_Screen(void);
void lcd_I2C_GOTO_XY(unsigned char row, unsigned char col);
void lcd_I2C_display_number(int Number);
void lcd_I2C_display_Real_number(double Number);




#endif /* LCD_H_ */
