# LCD Library

This is a library for interfacing with an LCD screen using AVR microcontrollers. It includes functions for initializing the LCD, clearing the screen, sending commands, sending characters, displaying numbers, and moving the cursor.

## Usage

1. Include the header file `LCD.h` in your AVR project.
2. Initialize the LCD by calling `lcd_init()`.
3. Use the available functions to display data on the screen.

## Functions

- `void lcd_init(void)` - Initializes the LCD and sets the mode to either 4-bit or 8-bit.
- `void lcd_Send_Command(unsigned char command)` - Sends a command to the LCD.
- `void lcd_Send_Char(unsigned char character)` - Sends a character to the LCD.
- `void lcd_send_String(char *string)` - Sends a string to the LCD.
- `void lcd_display_number(int Number)` - Displays an integer number on the LCD.
- `void lcd_display_Real_number(double Number)` - Displays a floating point number on the LCD.
- `void lcd_GOTO_XY(unsigned char row, unsigned char col)` - Moves the cursor to a specified position.
- `void lcd_Clear_Screen(void)` - Clears the LCD screen.
