/*
 * NVIC.h
 *
 *  Created on: 20 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_NVIC_H_
#define INC_NVIC_H_

//=======================
//       Includes
//=======================
#include "../lib/STM32_F103x6.h"

//===============================================
//Macros Configuration References
//===============================================
// @ref IRQ_number
#define NVIC_EXTI0              6
#define NVIC_EXTI1              7
#define NVIC_EXTI2              8
#define NVIC_EXTI3              9
#define NVIC_EXTI4              10
#define NVIC_EXTI5              23
#define NVIC_EXTI6              23
#define NVIC_EXTI7              23
#define NVIC_EXTI8              23
#define NVIC_EXTI9              23
#define NVIC_EXTI10             40
#define NVIC_EXTI11             40
#define NVIC_EXTI12             40
#define NVIC_EXTI13             40
#define NVIC_EXTI14             40
#define NVIC_EXTI15             40
#define NVIC_TIM1_UP_TIM10      25
#define NVIC_TIM1_TRG_COM_TIM11 26
#define NVIC_TIM2               28
#define NVIC_TIM3               29
#define NVIC_TIM4               30
#define NVIC_SPI1               35
#define NVIC_SPI2               36
#define NVIC_USART1             37
#define NVIC_USART2             38
#define NVIC_USART3             39
#define NVIC_ADC1               18
#define NVIC_ADC2               18
#define NVIC_ADC3               39
#define NVIC_DMA1_CH1           11
#define NVIC_DMA1_CH2           12
#define NVIC_DMA1_CH3           13
#define NVIC_DMA1_CH4           14
#define NVIC_DMA1_CH5           15
#define NVIC_DMA1_CH6           16
#define NVIC_DMA1_CH7           17
#define NVIC_DMA2_CH1           56
#define NVIC_DMA2_CH2           57
#define NVIC_DMA2_CH3           58
#define NVIC_DMA2_CH4           59
#define NVIC_DMA2_CH5           59
#define NVIC_I2C1_EV            31
#define NVIC_I2C1_ER            32
#define NVIC_I2C2_EV            33
#define NVIC_I2C2_ER            34

// @ref Groups_Subs
typedef enum{
	_4G_0S= 0x50FA0300,  	// 16 Priority group, 0 Sub priority
	_3G_1S= 0x50FA0400,		// 8 Priority group, 2 Sub priority
	_2G_2S= 0x50FA0500,  	// 4 Priority group, 4 Sub priority
	_1G_3S= 0x50FA0500,		// 2 Priority group, 8 Sub priority
	_0G_0S= 0x50FA0700		// 0 Priority group, 16 Sub priority

}NVIC_Group_Sub_t;

/*
* ===============================================
*      APIs Supported by "MCAL NVIC DRIVER"
* ===============================================
*/
void NVIC_Enable(uint8 IRQ_Number);
void NVIC_Disable(uint8 IRQ_Number);
void NVIC_setPending(uint8 IRQ_Number);
void NVIC_clearPending(uint8 IRQ_Number);
uint8 NVIC_getActiveBit(uint8 IRQ_Number);
void NVIC_setPriority(NVIC_Group_Sub_t bitNum, uint8 subPriority, uint8 groupPriority  , uint8 intNum);


#endif /* INC_NVIC_H_ */
