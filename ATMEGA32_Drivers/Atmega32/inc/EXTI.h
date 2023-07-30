/*
 * EXTI.h
 *
 *  Created on: 29 Jul 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_EXTI_H_
#define ATMEGA32_INC_EXTI_H_

#include "Atmega32.h"
#include "../../Library/BIT_MATH.h"
/*
 * @ref EXTI_Define
 */
#define EXTI0				6
#define EXTI1				7
#define EXTI2				5
/*
 * @ref Index_Define
 */
#define EXTI0_Index			0
#define EXTI1_Index			1
#define EXTI2_Index			2

/*
 * @ref Edge_Define
 */
#define Rising_Edge			0
#define Falling_Edge	    1
#define Low_Level			2
#define Any_change			3


void EXTI_Enable(uint8 Index , uint8 Edge);
void EXTI_Disable(uint8 Index );
void EXTI_setCallBackFunction(uint8 Index , void (*Ptr)(void));

#endif /* ATMEGA32_INC_EXTI_H_ */
