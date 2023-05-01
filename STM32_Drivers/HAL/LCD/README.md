# LCD Library

This library provides functions to interface with a Liquid Crystal Display (LCD) in 4-bit mode using STM32F103C8T6 microcontroller. It includes initialization of the LCD, sending commands and data to the LCD, and checking the busy status of the LCD.

## Getting Started

### Prerequisites

- STM32F103C8T6 microcontroller
- Keil uVision 5
- STM32F10x Standard Peripherals Library

### Installing

1. Clone the repository to your local machine.
2. Open the project in Keil uVision 5.
3. Add the `LCD.h` and `LCD.c` files to your project.
4. Include the `LCD.h` header file in your main program.

```c
#include "LCD.h"
```

### Usage

#### Initialization

Before using the LCD, it must be initialized using the `lcd_init()` function.

```c
lcd_init();
```

This function configures the data and control pins of the LCD, sets the cursor to the first line, and turns on the display with cursor blinking.

#### Sending Commands

Commands can be sent to the LCD using the `lcd_Send_Command()` function. The function takes a single parameter which is the command to be sent.

```c
lcd_Send_Command(CURSOR_FIRST_LINE);
```

#### Sending Data

Data can be sent to the LCD using the `lcd_Send_Data()` function. The function takes a single parameter which is the data to be sent.

```c
lcd_Send_Data('H');
lcd_Send_Data('e');
lcd_Send_Data('l');
lcd_Send_Data('l');
lcd_Send_Data('o');
```

#### Checking Busy Status

The busy status of the LCD can be checked using the `isBusy()` function. This function checks the busy flag of the LCD and waits until the flag is cleared before returning.

```c
isBusy();
```
