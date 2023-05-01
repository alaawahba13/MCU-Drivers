# HAL Folder README

The HAL (Hardware Abstraction Layer) folder contains two drivers for interfacing with an LCD and a keypad using a microcontroller.

## LCD Driver

The `LCD.c` and `LCD.h` files provide functions for initializing the LCD, writing to it, and setting the cursor position. The driver supports both 8-bit and 4-bit modes of communication with the LCD. The following functions are provided by the driver:

- `LCD_init()`: initializes the LCD by setting up the data pins, enabling the display, and setting the cursor to the home position.
- `LCD_sendCommand()`: sends a command to the LCD, such as clearing the display, setting the cursor position, or changing the display mode.
- `LCD_sendData()`: sends a character to the LCD to display on the screen.
- `LCD_setCursorPosition()`: sets the cursor position to a specific row and column on the screen.

## Keypad Driver

The `Keypad.c` and `Keypad.h` files provide functions for interfacing with a keypad using a matrix of buttons. The driver uses a 4x4 matrix of buttons and scans the rows and columns to detect when a button is pressed. The following functions are provided by the driver:

- `Keypad_init()`: initializes the GPIO pins for scanning the keypad matrix by setting the columns as output pins and the rows as input pins with pull-up resistors.
- `Keypad_getKey()`: scans the keypad matrix and returns the character corresponding to the button that was pressed.

Both drivers are designed to be used with a microcontroller that has GPIO pins to interface with the LCD and keypad. The drivers can be easily modified to work with different pin configurations by changing the pin numbers defined in the header files.
## Author

These Drivers were created by Alaa Wahba.
