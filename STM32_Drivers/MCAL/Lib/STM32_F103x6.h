/*
 * STM32_F103xx.h
 *
 *  Created on: Jan 15, 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_STM32_F103X6_H_
#define INC_STM32_F103X6_H_

//-----------------------------
//Includes
#include <stdio.h>
#include "Platform_types.h"
#include "BIT_MATH.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_BASE													0x08000000
#define SYSTEM_Memory_BASE													0x1FFFF000
#define SRAM_BASE 															0x20000000
#define Periphrals_BASE 													0x40000000
#define CORTEX_M3_Internal_Periphrals_BASE 									0xE0000000
#define NVIC_BASE 															0xE000E100
#define SYSTICK_BASE 														0xE000E010
//-----------------------------
//Base addresses for ABP2 Peripherals
//-----------------------------
//GPIO

// A,B fully included in LQFP48 Package
#define GPIOA_BASE															0x40010800
#define GPIOB_BASE															0x40010C00
// C,D partially included in LQFP48 Package
#define GPIOC_BASE 															0x40011000
#define GPIOD_BASE 															0x40011400
// E not included in LQFP48 Package
#define GPIOE_BASE 															0x40011800
//EXTI
#define EXTI_BASE 															0x40010400
//AFIO
#define AFIO_BASE 															0x40010000
//USART
#define USART1_BASE 														0x40013800
//SPI
#define SPI1_BASE 															0x40013000
//ADC
#define ADC1_BASE 															0x40012400
#define ADC2_BASE 															0x40012800
#define ADC3_BASE 															0x40013C00



//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
//RCC
#define RCC_BASE 														    0x40021000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
//USART
#define USART2_BASE 														0x40004400
#define USART3_BASE 														0x40004800
#define SPI2_BASE 															0x40003800
#define I2C1_BASE 															0x40005400
#define I2C2_BASE 															0x40005800

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;

}GPIO_Registers_t;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 ABP2ENR;
	volatile uint32 ABP1ENR;
	volatile uint32 BDCR ;
	volatile uint32 CSR;
}RCC_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;

}EXTI_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: NVIC
//-*-*-*-*-*-*-*-*-*-*-*
#define ISER0   	 (*(volatile uint32*)(NVIC_BASE+0x000))
#define ISER1   	 (*(volatile uint32*)(NVIC_BASE+0x004))
#define ISER2   	 (*(volatile uint32*)(NVIC_BASE+0x008))

#define ICER0   	 (*(volatile uint32*)(NVIC_BASE+0x080))
#define ICER1   	 (*(volatile uint32*)(NVIC_BASE+0x084))
#define ICER2   	 (*(volatile uint32*)(NVIC_BASE+0x088))

#define ISPR0   	 (*(volatile uint32*)(NVIC_BASE+0x100))
#define ISPR1   	 (*(volatile uint32*)(NVIC_BASE+0x104))
#define ISPR2   	 (*(volatile uint32*)(NVIC_BASE+0x108))

#define ICPR0   	 (*(volatile uint32*)(NVIC_BASE+0x180))
#define ICPR1 	     (*(volatile uint32*)(NVIC_BASE+0x184))
#define ICPR2	     (*(volatile uint32*)(NVIC_BASE+0x188))

#define IABR0  		 (*(volatile uint32*)(NVIC_BASE+0x200))
#define IABR1  		 (*(volatile uint32*)(NVIC_BASE+0x204))
#define IABR2  		 (*(volatile uint32*)(NVIC_BASE+0x208))

#define IPR	    	 ((volatile uint32*)(NVIC_BASE+0x300))

#define SCB_AIRCR    (*(volatile uint32*)(NVIC_BASE+0x0C))

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:  SYSTICK
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 CTRL;
	volatile uint32 LOAD;
	volatile uint32 VAL;
	volatile uint32 CALIB;
}SYSTICK_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:  AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 Resverved;
	volatile uint32 MAPR2;
}AFIO_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 BRR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 CR3;
	volatile uint32 GTPR;

}USART_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 CRCPR;
	volatile uint32 RXCRCR;
	volatile uint32 TXCRCR;
	volatile uint32 I2SCFGR;
	volatile uint32 I2SPR;

}SPI_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 ORA1;
	volatile uint32 ORA2;
	volatile uint32 DR;
	volatile uint32 SR1;
	volatile uint32 SR2;
	volatile uint32 CCR;
	volatile uint32 TRISE;

}I2C_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: ADC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32 SR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SMPR1;
	volatile uint32 SMPR2;
	volatile uint32 JOFR[4];
	volatile uint32 HTR;
	volatile uint32 LTR;
	volatile uint32 SQR[3];
	volatile uint32 JSQR;
	volatile uint32 JDR[4];
	volatile uint32 DR;
}ADC_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA 					((GPIO_Registers_t * )(GPIOA_BASE))
#define GPIOB 					((GPIO_Registers_t * )(GPIOB_BASE))
#define GPIOC 					((GPIO_Registers_t * )(GPIOC_BASE))
#define GPIOD 					((GPIO_Registers_t * )(GPIOD_BASE))
#define GPIOE 					((GPIO_Registers_t * )(GPIOE_BASE))

#define RCC 					((RCC_Registers_t  * )RCC_BASE)

#define SYSTICK 				((SYSTICK_Registers_t  * )SYSTICK_BASE)

#define EXTI 					((EXTI_Registers_t * )(EXTI_BASE))

#define AFIO 					((AFIO_Registers_t * )(AFIO_BASE))

#define USART1					((USART_Registers_t * )(USART1_BASE))
#define USART2					((USART_Registers_t * )(USART2_BASE))
#define USART3					((USART_Registers_t * )(USART3_BASE))

#define SPI1 					((SPI_Registers_t * )(SPI1_BASE))
#define SPI2 					((SPI_Registers_t * )(SPI2_BASE))

#define I2C1 					((I2C_Registers_t * )(I2C1_BASE))
#define I2C2 					((I2C_Registers_t * )(I2C2_BASE))

#define ADC1 					((ADC_Registers_t * )(ADC1_BASE))
#define ADC2 					((ADC_Registers_t * )(ADC2_BASE))
#define ADC3 					((ADC_Registers_t * )(ADC3_BASE))


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//External Interrupt Macros:
//-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-

//Line Number

#define EXTI0 				0
#define EXTI1 				1
#define EXTI2 				2
#define EXTI3 				3
#define EXTI4 				4
#define EXTI5 				5
#define EXTI6 				6
#define EXTI7 				7
#define EXTI8 				8
#define EXTI9 				9
#define EXTI10 				10
#define EXTI11 				11
#define EXTI12 				12
#define EXTI13 				13
#define EXTI14 				14
#define EXTI15 				15



#endif /* INC_STM32_F103X6_H_ */
