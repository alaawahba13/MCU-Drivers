# USART Library

This library provides functions for initializing and controlling USART (Universal Synchronous Asynchronous Receiver Transmitter) peripheral on STM32 microcontrollers. It supports asynchronous mode with 8 MHz clock speed. The library has the following functions:

## Functions

### `USART_init`

Initializes USART peripheral with given configuration. Supported features for now are only Asynchronous mode and 8 MHz system clock speed. It takes the following arguments:
* `USARTx`: A pointer to the USART peripheral you want to initialize (USART1, USART2 or USART3).
* `pinConfig`: A pointer to `USART_pinConfig_t` struct that contains USART configurations including:
	* `BaudRate`: Baud rate of the USART communication.
	* `DataLength`: Data length of USART data frame (7, 8 or 9 bits).
	* `Parity`: Parity configuration (None, Even or Odd).
	* `StopBits`: Number of stop bits (1, 0.5 or 2).
	* `FlowControl`: Flow control configuration (None, CTS, RTS or Both).
	* `USART_Mode`: Transmitter and/or Receiver mode.

### `USART_DeInit`

Resets the USART peripheral. It takes the following argument:
* `USARTx`: A pointer to the USART peripheral you want to reset.

### `USART_SetPins`

Initializes the GPIO pins used by the USART peripheral. It takes the following argument:
* `USARTx`: A pointer to the USART peripheral you want to initialize the GPIO pins for.

## Generic Variables

* `Global_pinConfig`: A pointer to the `USART_pinConfig_t` struct that contains the USART configurations.