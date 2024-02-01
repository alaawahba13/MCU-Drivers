# RCC Module Readme

This module contains functions to configure and read the clock settings of the microcontroller using the RCC (Reset and Clock Control) registers.

## Included Files
- `RCC.h`: Header file containing function declarations and constant values used by the module.
- `RCC.c`: Source file containing the implementation of the functions declared in the header file.

## Functions

### `uint32 RCC_getSYSCLK_Freq(void)`
This function returns the frequency of the system clock (SYSCLK) based on the current configuration of the RCC registers.

### `uint32 RCC_getPCKL1_Freq(void)`
This function returns the frequency of the peripheral clock 1 (PCLK1) based on the current configuration of the RCC registers.

### `uint32 RCC_getPCKL2_Freq(void)`
This function returns the frequency of the peripheral clock 2 (PCLK2) based on the current configuration of the RCC registers.

### `uint32 RCC_getHCKL_Freq(void)`
This function returns the frequency of the AHB bus clock (HCLK) based on the current configuration of the RCC registers.

## Constant Values

### `uint8 APB_PrescTable[8U]`
This constant array maps the value of the APB1 prescaler bits in the RCC registers to the corresponding division factor for the peripheral clock 1 (PCLK1).

### `uint8 AHB_PrescTable[16U]`
This constant array maps the value of the AHB prescaler bits in the RCC registers to the corresponding division factor for the AHB bus clock (HCLK).

## Usage

To use this module, include the `RCC.h` header file in your project and call the desired functions to read clock frequencies or configure the clock settings of the microcontroller using the RCC registers.