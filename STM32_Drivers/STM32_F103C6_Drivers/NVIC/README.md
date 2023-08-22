# NVIC (Nested Vectored Interrupt Controller) Driver 

## Introduction
The `NVIC.c` file is a driver for configuring and managing interrupts using the Nested Vectored Interrupt Controller (NVIC) on an embedded system. This driver provides functions to enable and disable specific interrupt sources in the NVIC.

## Author
- Author: Alaa Wahba

## Table of Contents
- [Includes](#includes)
- [NVIC Enable](#nvic-enable)
- [NVIC Disable](#nvic-disable)

## Includes
The `NVIC.c` file includes necessary header files for its functionality.

## NVIC Enable
### `void NVIC_Enable(uint8 IRQ_Number)`
This function enables the NVIC interrupt for a specified interrupt source. It accepts an `IRQ_Number` parameter, which represents the specific interrupt source to be enabled.

The `IRQ_Number` parameter should correspond to the interrupt number you want to enable. The NVIC supports multiple interrupt sources, and the function handles the correct register and bit manipulation to enable the specified interrupt.

## NVIC Disable
### `void NVIC_Disable(uint8 IRQ_Number)`
This function disables the NVIC interrupt for a specified interrupt source. It accepts an `IRQ_Number` parameter, which represents the specific interrupt source to be disabled.

The `IRQ_Number` parameter should correspond to the interrupt number you want to disable. The NVIC supports multiple interrupt sources, and the function handles the correct register and bit manipulation to disable the specified interrupt.

## Usage
To use this NVIC driver, include the `NVIC.h` header file in your project and call the provided functions to enable or disable specific interrupt sources as needed. Make sure to specify the correct `IRQ_Number` for the desired interrupt.

```c
// Example usage to enable interrupt with IRQ_Number 15
NVIC_Enable(15);

// Example usage to disable interrupt with IRQ_Number 10
NVIC_Disable(10);
```

