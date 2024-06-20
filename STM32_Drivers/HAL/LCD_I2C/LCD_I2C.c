/*
 * LCD.c
 *
 *  Created on: 14 Jan 2023
 *      Author: Alaa Wahba
 */

#include "LCD_I2C.h"

static int count = 0;
int G_cols, G_rows;
static I2C_Registers_t *G_I2Cx;
void lcd_I2C_init(int cols, int rows, I2C_Registers_t *I2Cx) {
	G_cols = cols;
	G_rows = rows;
	G_I2Cx = I2Cx;
	I2C_pinConfig_t I2C_pinConfig;
	I2C_pinConfig.Clock_Speed = I2C_CLK_SM_100K;
	I2C_pinConfig.I2C_Mode = I2C_Mode_I2C;
	I2C_pinConfig.Stretch_Mode = I2C_Stretch_EN;
	I2C_pinConfig.ACK_Enable = I2C_ACK_EN;
	I2C_pinConfig.P_Slave_CallBack_Fun = NULL;
	I2C_pinConfig.slave_address.slave_address_mode = I2C_Slave_7Bit;
	I2C_pinConfig.slave_address.slave_primary_address = 0;
	I2C_pinConfig.slave_address.Enable_Dual_Mode = 0;

	I2C_GPIO_SetPins(I2Cx);
	I2C_init(&I2C_pinConfig, I2Cx);
	STK_init();
	// you must wait for the hardware to initialize
	STK_delayMs(50);
	lcd_I2C_Send_Command(FUNCTION_4BIT_2LINES);
	lcd_I2C_Send_Command(ENTRY_MODE);
	lcd_I2C_Send_Command(CURSOR_FIRST_LINE);
	lcd_I2C_Send_Command(DISPLAY_ON_CURSOR_BLINK);
	lcd_I2C_Clear_Screen();

}
void lcd_I2C_Send_Command(char cmd) {
	/*
	 * 1.Write command to port
	 * 2.Reset control pins
	 * 3.Deactivate and Activate Enable
	 */
	char data_u, data_l;
	uint8 data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0
	I2C_Master_TX(G_I2Cx, SLAVE_ADDRESS_LCD, (uint8*) data_t, 4, STOP,
			NO_REPEATED_START);
	STK_delayMs(10);

}
void lcd_I2C_Send_Char(char data) {

	char data_u, data_l;
	uint8 data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;  //en=1, rs=1
	data_t[1] = data_u | 0x09;  //en=0, rs=1
	data_t[2] = data_l | 0x0D;  //en=1, rs=1
	data_t[3] = data_l | 0x09;  //en=0, rs=1
	I2C_Master_TX(G_I2Cx, SLAVE_ADDRESS_LCD, (uint8*) data_t, 4, STOP,
			NO_REPEATED_START);

	if (count == G_cols) {
		lcd_I2C_GOTO_XY(1, 0);
	}
#if (LCD_4x20 || LCD_4x16)
	if (count == G_cols * 2) {
		lcd_I2C_GOTO_XY(2, 0);
	} else if (count == G_cols * 3) {
		lcd_I2C_GOTO_XY(3, 0);
	}
#endif

	// if both lines are full clear and start over.
	else if (count == (G_cols * G_rows)) {
		lcd_I2C_Clear_Screen();
		lcd_I2C_GOTO_XY(0, 0);
		count = 0;
	}

	count++;
}
void lcd_I2C_Clear_Screen(void) {
	lcd_I2C_Send_Command(CLEAR_SCREEN);
	count =0;
}

void lcd_I2C_GOTO_XY(unsigned char row, unsigned char col) {
	if (col >= G_cols || col < 0)
		return; // Invalid column, do nothing

	switch (row) {
	case 0:
		lcd_I2C_Send_Command(CURSOR_FIRST_LINE + col);
		break;
	case 1:
		lcd_I2C_Send_Command(CURSOR_SECOND_LINE + col);
		break;
#if (LCD_4x20)
	        case 2:
	            lcd_I2C_Send_Command(CURSOR_THIRD_LINE_20 + col);
	            break;
	        case 3:
	            lcd_I2C_Send_Command(CURSOR_FOURTH_LINE_20 + col);
	            break;
	#endif
#if (LCD_4x16)
        case 2:
            lcd_I2C_Send_Command(CURSOR_THIRD_LINE_16 + col);
            break;
        case 3:
            lcd_I2C_Send_Command(CURSOR_FOURTH_LINE_16 + col);
            break;
#endif
	default:
		// Handle invalid row number if necessary
		break;
	}
}

void lcd_I2C_display_number(int Number) {
	char str[7];
	// Converts Int to String
	sprintf(str, "%d", Number);
	lcd_I2C_send_String(str);
}
void lcd_I2C_display_Real_number(double Number) {
	char str[16];
	char *tmpSign = (Number > 0) ? "" : "-";
	float tmpNum = (Number > 0) ? Number : -Number;

	int tmpVal = tmpNum;
	float tmpFrac = tmpNum - tmpVal;

	int Frac = tmpFrac * 100;

	sprintf(str, "%s%d.%02d", tmpSign, tmpVal, Frac);
	lcd_I2C_send_String(str);

}
void lcd_I2C_send_String(char *string) {

	while (*string > 0) {
		lcd_I2C_Send_Char(*string++);

	}
}

