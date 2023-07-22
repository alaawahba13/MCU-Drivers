# Keypad Driver

This is a driver for a 4x4 matrix keypad. The driver provides a function to initialize the keypad and a function to get the key pressed. The keypad uses the columns as output and the rows as input to detect the button presses.

## Initialization

To initialize the keypad, call the `Keypad_init()` function. This function sets the columns as output and the rows as input. The columns are used to scan the buttons by writing ground to each column sequentially. The rows are input so if the button is pressed it's connected to ground.

## Get Key Pressed

To get the key pressed, call the `Keypad_Get_Key()` function. This function scans the keypad and returns the character corresponding to the button pressed. If no button is pressed, it returns the character 'A'.

## Usage Example

```c
#include "Keypad.h"
#include "LCD.h"

int main()
{
    char key_pressed;

    Keypad_init();
    LCD_init();

    while(1)
    {
        key_pressed = Keypad_Get_Key();

        if(key_pressed != 'A')
        {
            LCD_send_char(key_pressed);
        }
    }
}
```

In this example, the keypad is initialized and the LCD is initialized. Then, in an infinite loop, the keypad is scanned to get the key pressed. If a key is pressed, the character is displayed on the LCD.

## Author

The driver was created by Alaa Wahba on January 17, 2023.

