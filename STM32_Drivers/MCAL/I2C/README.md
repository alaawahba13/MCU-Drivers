# I2C Driver 

## Introduction
The `I2C.c` file is an I2C (Inter-Integrated Circuit) driver for embedded systems. It provides functions and configurations to work with I2C communication using the STM32 microcontroller family. This driver supports both master and slave modes of I2C communication.

## Author
- Author: Alaa Wahba

## Table of Contents
- [Includes](#includes)
- [Generic Variables](#generic-variables)
- [Generic Functions](#generic-functions)
- [I2C Initialization](#i2c-initialization)
- [I2C Deinitialization](#i2c-deinitialization)
- [I2C GPIO Configuration](#i2c-gpio-configuration)
- [I2C Master Transmit](#i2c-master-transmit)
- [I2C Master Receive](#i2c-master-receive)
- [I2C Generate Start Condition](#i2c-generate-start-condition)
- [I2C Generate Stop Condition](#i2c-generate-stop-condition)
- [I2C ACK Configuration](#i2c-ack-configuration)
- [I2C Get Flag Status](#i2c-get-flag-status)
- [I2C Send Slave Address](#i2c-send-slave-address)
- [I2C Slave Transmit](#i2c-slave-transmit)
- [I2C Slave Receive](#i2c-slave-receive)
- [I2C1 Event Interrupt Handler](#i2c1-event-interrupt-handler)
- [Slave State Handling](#slave-state-handling)

## Includes
The `I2C.c` file includes necessary header files for its functionality.

## Generic Variables
- `Global_I2C_pinConfig`: An array of structures to store I2C pin configurations for two I2C interfaces.
- Constants `I2C1_Index` and `I2C2_Index` are used as indices for the I2C interfaces.

## Generic Functions
### I2C Initialization
```c
void I2C_init(I2C_pinConfig_t *I2C_pinConfig, I2C_Registers_t *I2Cx)
```
This function initializes the I2C interface. It configures clock settings, frequency, and mode for the I2C communication.

### I2C Deinitialization
```c
void I2C_Deinit(I2C_Registers_t *I2Cx)
```
This function deinitializes the I2C interface, resetting its settings and disabling interrupts.

### I2C GPIO Configuration
```c
void I2C_GPIO_SetPins(I2C_Registers_t *I2Cx)
```
Configures GPIO pins for I2C communication based on the selected I2C interface.

### I2C Master Transmit
```c
void I2C_Master_TX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data, uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start)
```
Transmits data in master mode over the I2C interface.

### I2C Master Receive
```c
void I2C_Master_RX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data, uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start)
```
Receives data in master mode over the I2C interface.

### I2C Generate Start Condition
```c
void I2C_GenerateStart(I2C_Registers_t *I2Cx, Repeated_Start_t start, Functional_State_t State)
```
Generates a start condition for I2C communication.

### I2C Generate Stop Condition
```c
void I2C_GenerateStop(I2C_Registers_t *I2Cx, Functional_State_t State)
```
Generates a stop condition for I2C communication.

### I2C ACK Configuration
```c
void I2C_ACKConfig(I2C_Registers_t *I2Cx, Functional_State_t State)
```
Configures ACK (acknowledge) for I2C communication.

### I2C Get Flag Status
```c
FlagStatus I2C_GetFlagStatus(I2C_Registers_t *I2Cx, Status Flag)
```
Checks the status of various flags in the I2C interface.

### I2C Send Slave Address
```c
void I2C_SendSlaveAddress(I2C_Registers_t *I2Cx, uint16 slaveAddress, I2C_Direction_t Direction)
```
Sends the slave address in I2C communication, supporting 7-bit addressing mode.

### I2C Slave Transmit
```c
void I2C_Slave_TX(I2C_Registers_t *I2Cx, uint8 data)
```
Transmits data in slave mode over the I2C interface.

### I2C Slave Receive
```c
uint8 I2C_Slave_RX(I2C_Registers_t *I2Cx)
```
Receives data in slave mode over the I2C interface.

### I2C1 Event Interrupt Handler
```c
void I2C1_EV_IRQHandler(void)
```
Handles interrupts for I2C1 events.

### Slave State Handling
```c
void Slave_States(I2C_Registers_t* I2Cx, Slave_state state)
```
Handles various slave states during I2C communication.

## Usage
To use this I2C driver, include the `I2C.h` header file in your project and call the provided functions to configure and communicate over the I2C interface. Refer to the comments in the code for detailed explanations of each function.

