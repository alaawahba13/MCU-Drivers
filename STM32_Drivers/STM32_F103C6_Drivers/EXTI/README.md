README.md

# EXTI Driver

This is a driver for EXTI (External Interrupt) module in STM32 microcontrollers. The driver provides an interface to configure and enable EXTI pins.

## File Structure

```
├── EXTI.h
├── EXTI.c
└── README.md
```

* `EXTI.h` contains the function prototypes and necessary macros for EXTI configuration.
* `EXTI.c` contains the implementation of the functions declared in `EXTI.h`.
* `README.md` is a file that explains the purpose and usage of the driver.

## Dependencies

This driver depends on the following:

* STM32F103C8T6 Microcontroller
* CMSIS Library version 1.0.0

## How to Use

To use the driver, follow these steps:

1. Include `EXTI.h` in your project source code.
2. Initialize the pin configuration structure of type `EXTI_PinConfig_t` with the desired values. The configuration structure must be initialized with the following:
	- `pinMapping` : contains the GPIO port and pin number that will be used for EXTI
	- `triggerEdge` : contains the desired trigger edge (rising edge, falling edge or both)
	- `enable` : contains the enable status of the EXTI pin (enabled or disabled)
	- `callback` : contains a pointer to a function that will be called when the EXTI interrupt occurs
3. Call the function `Update_EXTI()` and pass the address of the configuration structure as a parameter.
4. Implement the callback function to handle the interrupt that will be triggered by EXTI.

## Contributors

* Alaa Wahba (alaawahba3@gmail.com)

