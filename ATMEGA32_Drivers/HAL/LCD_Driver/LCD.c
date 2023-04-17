/*
 * LCD.c
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#include "LCD.h"

void isBusy(void){
	// Set the data port as input
	LCD_DDR &= ~(0xFF <<DATA_SHIFT) ;
	// Set RW = 1 to read && Command mode >> RS =0
	SET(LCD_CONTROL_PORT,ReadWrite);
	CLEAR(LCD_CONTROL_PORT, REGISTER_SELECT);
	// wait for the enable cycle
	lcd_kick();
	CLEAR(LCD_CONTROL_PORT, ReadWrite); //write
}

void lcd_init(){
	// you must wait for the hardware to initialize
	_delay_ms(20);
	// set port as ouput to write commands
	LCD_DDR= 0xFF;
	// set three control pins as output and write 0
	LCD_CONTROL_DDR |= (1<<ENABLE_SWITCH | 1<<REGISTER_SELECT | 1<<ReadWrite);
	LCD_CONTROL_PORT &= ~(1<<ENABLE_SWITCH | 1<<REGISTER_SELECT | 1<<ReadWrite);
	_delay_ms(15);
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
void lcd_Send_Command(unsigned char command){

#ifdef EIGHT_BIT_MODE
	isBusy();
	// 1.Write
	LCD_PORT = command;
	// 2.Reset
	LCD_CONTROL_PORT &= ~ ((1<<ReadWrite) | (1<< REGISTER_SELECT));
	// 3. Reactivate Enable
	lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	isBusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CONTROL_PORT &= ~ ((1<<ReadWrite) | (1<< REGISTER_SELECT));
	//_delay_ms(1);
	lcd_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CONTROL_PORT &= ~ ((1<<ReadWrite) | (1<< REGISTER_SELECT));
	//_delay_ms(1);
	lcd_kick();
#endif

}
void lcd_Send_Char(unsigned char character){

#ifdef EIGHT_BIT_MODE
	isBusy();
	//1. set the RS to 1 to send data
	LCD_CONTROL_PORT |= (1<< REGISTER_SELECT);
	//2. Write data
	LCD_PORT = character;
	LCD_CONTROL_PORT &= ~ (1<<ReadWrite);
	// Reactivate Enable
	lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F ) | (character & 0xF0);
		LCD_CONTROL_PORT |= (1<< REGISTER_SELECT);
		LCD_CONTROL_PORT &= ~ (1<<ReadWrite);
		//_delay_ms(1);
		lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F ) | (character <<4);
		LCD_CONTROL_PORT |= (1<< REGISTER_SELECT);
		LCD_CONTROL_PORT &= ~ (1<<ReadWrite);
	//	_delay_ms(1);
		lcd_kick();
#endif
}
void lcd_send_String(char *string){
   // keeps track of chars count
	int count=0;
	while(*string >0){
		count++;
		lcd_Send_Char(*string++);
		// if first line is full go to second
		if (count == 16){
			lcd_GOTO_XY(1, 0);
		}
		// if both lines are full clear and start over.
		else if(count== 32 ){
			lcd_Clear_Screen();
			lcd_GOTO_XY(0, 0);
			count =0;
		}
	}
}
void lcd_GOTO_XY(unsigned char row , unsigned char col){

	if(row ==0 )
	{	if((col < 16) && (col>=0))
		lcd_Send_Command(CURSOR_FIRST_LINE +col);
	}
	else if (row ==1)
	{	if((col < 16) && (col>=0))
		lcd_Send_Command(CURSOR_SECOND_LINE+col);
	}

}
void lcd_Clear_Screen(void){
	lcd_Send_Command(CLEAR_SCREEN);
}
void lcd_display_number(int Number){
	char str[7];
	// Converts Int to String
	sprintf(str,"%d",Number);
	lcd_send_String(str);
}
void lcd_display_Real_number(double Number){
	char str[16];
	char *tmpSign  = (Number >0) ? "" : "-";
	float tmpNum    = (Number >0) ? Number : -Number;

	int tmpVal = tmpNum;
	float tmpFrac  = tmpNum - tmpVal;

	int Frac = tmpFrac * 10000;

	sprintf(str, "%s%d.%04d", tmpSign, tmpVal, Frac);
	lcd_send_String(str);

}
void lcd_kick(){
	// Enable =0 >> LCD Busy
	CLEAR(LCD_CONTROL_PORT, ENABLE_SWITCH);
	_delay_ms(50);
	SET(LCD_CONTROL_PORT, ENABLE_SWITCH);
}
