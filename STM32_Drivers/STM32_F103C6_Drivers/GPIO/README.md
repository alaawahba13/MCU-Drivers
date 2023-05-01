# GPIO Library for STM32F103C6

This library provides functions to configure GPIO pins of STM32F103C6 microcontroller.

## Functions

The library provides the following functions:

### 1. GPIO_init

```c
void GPIO_init(GPIO_Registers_t *GPIOx, GPIO_PinConfig_t *pinConfig);
```

This function is used to initialize the GPIO pin according to the specified configuration.

* `GPIOx`: Select the port where the x can be (A..E depending on device used).
* `pinConfig`: Pointer to a structure that contains the pin configuration information.

### 2. GPIO_DeInit

```c
void GPIO_DeInit(GPIO_Registers_t *GPIOx);
```

This function is used to reset all the GPIO registers.

* `GPIOx`: Select the port where the x can be (A..E depending on device used).

## Structure

The library uses the following structures:

### 1. GPIO_PinConfig_t

```c
typedef struct
{
	uint16 Pin_Number;  // specifies the GPIO pins to be configured.
	uint32 MODE;        // specifies the operating mode for the selected pins.
	uint32 Output_Speed;// Specifies the speed for the selected pins.
}GPIO_PinConfig_t;
```

This structure contains the pin configuration information.

* `Pin_Number`: Specifies the GPIO pins to be configured.
* `MODE`: Specifies the operating mode for the selected pins.
* `Output_Speed`: Specifies the speed for the selected pins.

### 2. GPIO_Registers_t

```c
typedef struct
{
	volatile uint32 CRL;  // GPIO port configuration register low.
	volatile uint32 CRH;  // GPIO port configuration register high.
	volatile uint32 IDR;  // GPIO port input data register.
	volatile uint32 ODR;  // GPIO port output data register.
	volatile uint32 BSRR; // GPIO port bit set/reset register.
	volatile uint32 BRR;  // GPIO port bit reset register.
	volatile uint32 LCKR; // GPIO port configuration lock register.
}GPIO_Registers_t;
```

This structure contains the registers of the GPIO port.

* `CRL`: GPIO port configuration register low.
* `CRH`: GPIO port configuration register high.
* `IDR`: GPIO port input data register.
* `ODR`: GPIO port output data register.
* `BSRR`: GPIO port bit set/reset register.
* `BRR`: GPIO port bit reset register.
* `LCKR`: GPIO port configuration lock register.

## Author

This library was created by Alaa Wahba.
