/*
 * RCC.h
 *
 *  Created on: 16 Feb 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
//=======================
//       Includes
//=======================
#include "../lib/STM32_F103x6.h"

//===============================================
//Macros Configuration References
//===============================================

#define HSI 		(uint32)8000000
#define HSE 		(uint32)8000000

typedef enum {
	AHB_NO_DIV = 0b000,					//	0bxx: SYSCLK not divided
	AHB_DIV_2 = 0b1000,					//	1000: SYSCLK divided by 2
	AHB_DIV_4 = 0b1001,					//	1001: SYSCLK divided by 4
	AHB_DIV_8 = 0b1010,					//	1010: SYSCLK divided by 8
	AHB_DIV_16 = 0b1011,					//	1011: SYSCLK divided by 16
	AHB_DIV_64 = 0b1100,					//	1100: SYSCLK divided by 64
	AHB_DIV_128 = 0b1101,					//	1101: SYSCLK divided by 128
	AHB_DIV_256 = 0b1110,					//	1110: SYSCLK divided by 256
	AHB_DIV_512 = 0b1111,					//	1111: SYSCLK divided by 512
} AHB_Prescalar_t;

typedef enum {
	APB_NO_DIV = 0b000,					//	0bbb: SYSCLK not divided
	APB_DIV_2 = 0b100,					//	1000: SYSCLK divided by 2
	APB_DIV_4 = 0b101,					//	1001: SYSCLK divided by 4
	APB_DIV_8 = 0b110,					//	1010: SYSCLK divided by 8
	APB_DIV_16 = 0b111,					//	1011: SYSCLK divided by 16

} APB_Prescalar_t;

typedef enum {
/*
 *  PLLMUL: PLL multiplication factor
 These bits are written by software to define the PLL multiplication factor. These bits can be
 written only when PLL is disabled.
 Caution: The PLL output frequency must not exceed 72 MHz.
 */
	PLL_MUL_2 = 0, 			//0000: PLL input clock x 2
	PLL_MUL_3,			//0001: PLL input clock x 3
	PLL_MUL_4,			// 0010: PLL input clock x 4
	PLL_MUL_5,			//0011: PLL input clock x 5
	PLL_MUL_6,			// 0100: PLL input clock x 6
	PLL_MUL_7,			//0101: PLL input clock x 7
	PLL_MUL_8,			//0110: PLL input clock x 8
	PLL_MUL_9,			// 0111: PLL input clock x 9
	PLL_MUL_10,
	PLL_MUL_11,
	PLL_MUL_12,
	PLL_MUL_13,
	PLL_MUL_14,
	PLL_MUL_15,
	PLL_MUL_16,
} PLL_MUL_t;
typedef enum {
	RCC_HSE = 0x01, RCC_HSI = 0x00, RCC_PLL = 0x10
} RCC_CLKSrc_t;

typedef enum {
	HSE_CRYSTAL, HSE_RC
} RCC_HSESrc_t;

typedef enum {
	PLL_HSE, PLL_HSI
} RCC_PLLSrc_t;

// @ref BUS_ID_define
#define APB1_ID 		0
#define APB2_ID 		1
#define AHB_ID 			2

// @ref Periphral_ID_define
#define GPIOA_ID		2
#define GPIOB_ID		3
#define GPIOC_ID		4
#define GPIOD_ID		5
#define GPIOE_ID		6

#define AFIO_ID			0

#define USART1_ID		14
#define USART2_ID		17
#define USART3_ID		18

#define SPI1_ID			12
#define SPI2_ID			14

#define I2C1_ID			21
#define I2C2_ID			22

#define ADC1_ID 		9
#define ADC2_ID 		10
#define ADC3_ID 		15

#define TIM1_ID 		11
#define TIM2_ID 		0
#define TIM3_ID 		1
#define TIM4_ID 		2

/*
 * ===============================================
 *      APIs Supported by "MCAL RCC DRIVER"
 * ===============================================
 */
uint32 RCC_getSYSCLK_Freq(void);

uint32 RCC_getPCKL1_Freq(void);
uint32 RCC_getPCKL2_Freq(void);
uint32 RCC_getHCKL_Freq(void);

void RCC_init(RCC_CLKSrc_t clkSrc, RCC_HSESrc_t HSESrc, RCC_PLLSrc_t PLLSrc,uint8 PLLMUL);
void RCC_CLK_RST(uint8 busID, uint8 periphralID);
void RCC_CLK_EN(uint8 busID, uint8 periphralID);
void RCC_setAPB1Prescalar(APB_Prescalar_t prescalar);
void RCC_setAPB2Prescalar(APB_Prescalar_t prescalar);
void RCC_setAHBPrescalar(AHB_Prescalar_t prescalar);
void RCC_setADCPrescalar(int prescalar);

#endif /* INC_RCC_H_ */
