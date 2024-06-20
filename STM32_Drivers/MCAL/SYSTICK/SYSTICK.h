/*
 * SYSTICK.h
 *
 *  Created on: 28 Feb 2024
 *      Author: Alaa
 */

#ifndef SYSTICK_SYSTICK_H_
#define SYSTICK_SYSTICK_H_

//=======================
//       Includes
//=======================

#include "../Lib/STM32_F103x6.h"
#include "../RCC/RCC.h"
//===============================================
//      Macros Configuration References
//===============================================
/*
 * Options: AHB_8
 * 			AHB
 */
#define AHB 		0
#define AHB_8		1
#define STK_CLK_SRC 	AHB
/*
 * Options: SINGLE
 * 			PERIODIC
 */
#define STK_MODE 		SINGLE

#define CPU_INPUT_CLOCK		RCC_getSYSCLK_Freq()
/*
* ===============================================
*      APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/
void STK_init();
void STK_stopInterval (void);
void STK_BusyWait(uint32 ticks);
void STK_SetInterval(uint32 time, void (*CB_ptr)(void));
uint32 STK_getElapsedTime();
uint32 STK_getRemainingTime();
void STK_delayMs(uint32 time);
void STK_delayUs(uint32 time);


#endif /* SYSTICK_SYSTICK_H_ */
