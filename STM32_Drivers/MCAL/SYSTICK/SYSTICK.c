/*
 * SYSTICK.c
 *
 *  Created on: 28 Feb 2024
 *      Author: Alaa
 */

//=======================
//       Includes
//=======================
#include "SYSTICK.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
static uint32 microSecond = 0;
void (*P_CallBack_Fun)(void);
/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void STK_init() {
#if STK_CLK_SRC == AHB_8
	SYSTICK->CTRL &= ~(1 << 2);
	microSecond = 1;		// Assuming system clock is HSI
#elif STK_CLK_SRC =AHB
	SYSTICK->CTRL |= (1<<2);
	microSecond = 8;		// Assuming system clock is HSI
#endif

}
void STK_BusyWait(uint32 ticks) {
	SYSTICK->LOAD = ticks;
	//Disable Interrupt
	SYSTICK->CTRL &= ~(1<<1);
	//Enable Systick
	SYSTICK->CTRL |= (1<<0);
	//Wait for flag
	while (!(SYSTICK->CTRL & (1<<16)));
	//Disable Systick
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL &= ~(1<<0);

}

void STK_delayMs(uint32 time) {
	for (uint32 i=0; i < time; i++) {
		SYSTICK->LOAD = 1000*microSecond;
		//Disable Interrupt
		CLEAR(SYSTICK->CTRL, 1);
		//Enable Systick
		SET(SYSTICK->CTRL, 0);
		//Wait for flag
		while (!GET(SYSTICK->CTRL, 16))
			;
		//Disable Systick
		SYSTICK->LOAD = 0;
		SYSTICK->VAL = 0;
		CLEAR(SYSTICK->CTRL, 0);
	}
}
void STK_delayUs(uint32 time) {
	SYSTICK->LOAD = time*microSecond;
	//Disable Interrupt
	CLEAR(SYSTICK->CTRL, 1);
	//Enable Systick
	SET(SYSTICK->CTRL, 0);
	//Wait for flag
	while (!GET(SYSTICK->CTRL, 16))
		;
	//Disable Systick
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;
	CLEAR(SYSTICK->CTRL, 0);
}
void STK_SetInterval(uint32 time, void (*CB_ptr)(void)) {
	SYSTICK->LOAD = time;
	//Enable Interrupt
	SET(SYSTICK->CTRL, 1);
	//Enable Systick
	SET(SYSTICK->CTRL, 0);
	//set Callback function
	P_CallBack_Fun = CB_ptr;
}
uint32 STK_getElapsedTime() {
	return (SYSTICK->LOAD - SYSTICK->VAL);
}
uint32 STK_getRemainingTime() {
	return (SYSTICK->VAL);

}

void SysTick_Handler() {
	uint8 flag = 0;
#if STK_MODE == SINGLE
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;
	CLEAR(SYSTICK->CTRL, 0);
	CLEAR(SYSTICK->CTRL, 1);
#endif

	P_CallBack_Fun();
	flag = GET(SYSTICK->CTRL, 16);
}
