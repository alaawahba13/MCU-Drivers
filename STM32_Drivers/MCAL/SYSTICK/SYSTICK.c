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
static uint32 microSecond = 1;
void (*P_CallBack_Fun)(void);
/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void STK_init() {
	// Set number of Ticks for one microsecond.
	microSecond = (uint32) CPU_INPUT_CLOCK / 1000000;

#if STK_CLK_SRC == AHB_8
	microSecond = microSecond/8;		// Assuming system clock is HSI
	CLEAR(SYSTICK->CTRL, 2);
#endif
#if STK_CLK_SRC == AHB
	SET(SYSTICK->CTRL, 2);
#endif
	SET(SYSTICK->CTRL, 0); // enable

}
void STK_BusyWait(uint32 ticks) {
	SYSTICK->LOAD = ticks;
	//Disable Interrupt
	SYSTICK->CTRL &= ~(1 << 1);
	//Enable Systick
	SYSTICK->CTRL |= (1 << 0);
	//Wait for flag
	while (!(SYSTICK->CTRL & (1 << 16)))
		;
	//Disable Systick
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL &= ~(1 << 0);

}

// Stop the SysTick timer from generating interrupts.
void STK_stopInterval(void) {
	/* Disable STK Interrupt */
	CLEAR(SYSTICK->CTRL, 1);

	/* Stop Timer */
	SET(SYSTICK->CTRL, 0);
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;

}

void STK_delayMs(uint32 time) {
	for (uint32 i = 0; i < time; i++) {

		//Enable Systick
		SET(SYSTICK->CTRL, 0);
		//Disable Interrupt
		CLEAR(SYSTICK->CTRL, 1);
		SYSTICK->LOAD = 1000 * microSecond;
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
	//Enable Systick
	SET(SYSTICK->CTRL, 0);
	//Disable Interrupt
	CLEAR(SYSTICK->CTRL, 1);

	SYSTICK->LOAD = time * microSecond;
	//Wait for flag
	while (!GET(SYSTICK->CTRL, 16))
		;
	//Disable Systick
	SYSTICK->LOAD = 0;
	SYSTICK->VAL = 0;
	CLEAR(SYSTICK->CTRL, 0);
}
void STK_SetInterval(uint32 time, void (*CB_ptr)(void)) {
	SYSTICK->VAL = 0;
	CLEAR(SYSTICK->CTRL, 0);

	SYSTICK->LOAD = time;
	//Enable Interrupt
	SET(SYSTICK->CTRL, 1);
	//Enable Systick
	SET(SYSTICK->CTRL, 0);
	//set Callback function
	P_CallBack_Fun = CB_ptr;
}
uint32 STK_getElapsedTime() {
	uint32 load = SYSTICK->LOAD;
	uint32 val1 = SYSTICK->VAL;
	uint32 val = (SYSTICK->LOAD - SYSTICK->VAL);
	return val;
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
