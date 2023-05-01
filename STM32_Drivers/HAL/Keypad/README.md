# Keypad.c

This is a C source file for a simple 4x4 keypad interface. It provides functions to initialize the keypad and to get the pressed key.

## Functionality

The keypad is a matrix of 4 rows and 4 columns, and is connected to a microcontroller. The Keypad_init function initializes the rows and columns of the keypad, configures them as output or input, and sets their initial state. The Keypad_Get_Key function scans the keypad by sequentially writing GND to each column and reading the corresponding row. It returns the ASCII code of the pressed key.

## Usage

To use this module, include the Keypad.h header file and link to the Keypad.c source file in your project. Call the Keypad_init function to initialize the keypad, and call the Keypad_Get_Key function to get the pressed key.

## Example

```c
#include "Keypad.h"

int main()
{
    char key;
    
    Keypad_init();
    
    while (1)
    {
        key = Keypad_Get_Key();
        if (key != 'A')
        {
            // do something with the key
        }
    }
    
    return 0;
}
```

