# SPI Driver

This is a device driver for the SPI (Serial Peripheral Interface) communication protocol. The driver contains functions to initialize, deinitialize, send and receive data using the SPI module.

## File Structure

- **SPI.c** : Contains the driver implementation functions.
- **SPI.h** : Contains the function prototypes, macros, enums, and data structures used in the driver.

## Usage

1. Include the `SPI.h` header file in your application code.
2. Initialize the SPI module using the `SPI_init()` function by providing the required configurations such as communication mode, data size, clock polarity, and phase, etc.
3. Send or receive data using the `SPI_SendData()` or `SPI_ReceiveData()` functions respectively.
4. Deinitialize the SPI module using the `SPI_DeInit()` function.

## Functions

- `void SPI_init(SPI_PinConfig_t *SPI_pinConfig, SPI_Registers_t *SPIx)`: Initializes the SPI module.
- `void SPI_DeInit(SPI_Registers_t *SPIx)`: Deinitializes the SPI module.
- `void SPI_SendData(SPI_Registers_t *SPIx, uint16 *pData, enum Polling_Mechanism PollingEn)`: Sends the data in `pData` to the slave device.
- `void SPI_ReceiveData(SPI_Registers_t *SPIx, uint16 *pData, enum Polling_Mechanism PollingEn)`: Receives the data from the slave device and stores it in `pData`.

## Data Structures

### `SPI_PinConfig_t`

- `uint8_t Commuincation_Mode`: Communication mode of SPI (full-duplex, half-duplex, or simplex).
- `uint8_t Data_Size`: Data size for SPI communication (8-bit, 16-bit).
- `uint8_t Frame_Format`: Frame format of SPI (MSB or LSB).
- `uint8_t NSS`: Slave select configuration.
- `uint8_t BaudRate`: Baud rate for SPI communication.
- `uint8_t CLK_Polarity`: Clock polarity.
- `uint8_t CLK_Phase`: Clock phase.
- `uint8_t IRQ_Enable`: Enables or disables interrupt mode.

### `SPI_Registers_t`

This structure contains pointers to the SPI registers.

## Macros

- `RCC_SPI1_CLK_EN()`: Enables the clock for SPI1.
- `RCC_SPI2_CLK_EN()`: Enables the clock for SPI2.
- `RCC_SPI1_CLK_Reset()`: Resets the clock for SPI1.
- `RCC_SPI2_CLK_Reset()`: Resets the clock for SPI2.
- `SPI_NSS_Hard_Master_SS_output_enable`: Enables hardware slave select.
- `SPI_NSS_Hard_Master_SS_output_disable`: Disables hardware slave select.
- `SPI_IRQ_EN_None`: Disables interrupt mode.
- `Enable`: Enables the polling mechanism.
- `Disable`: Disables the polling mechanism.