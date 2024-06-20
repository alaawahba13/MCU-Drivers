/*
 * RCC.c
 *
 *  Created on: 16 Feb 2023
 *      Author: Alaa Wahba
 */

//=======================
//       Includes
//=======================
#include "RCC.h"
/*
 *  APB Low-speed prescaler (APB1)
 Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
 0xx: HCLK not divided
 100: HCLK divided by 2
 101: HCLK divided by 4
 110: HCLK divided by 8
 111: HCLK divided by 16
 */
uint8 APB_PrescTable[8U] = { 0, 0, 0, 0, 1, 2, 3, 4 };

/*
 *  AHB prescaler
 Set and cleared by software to control AHB clock division factor.
 0xxx: SYSCLK not divided
 1000: SYSCLK divided by 2
 1001: SYSCLK divided by 4
 1010: SYSCLK divided by 8
 1011: SYSCLK divided by 16
 1100: SYSCLK divided by 64
 1101: SYSCLK divided by 128
 1110: SYSCLK divided by 256
 1111: SYSCLK divided by 512
 */
uint8 AHB_PrescTable[16U] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9 };
uint32 RCC_getSYSCLK_Freq(void) {
	/*
	 * 	00: HSI selected as system clock
	 01: HSE selected as system clock
	 10: PLL selected as system clock
	 */
	uint8 SW = (RCC->CFGR >> 2) & 0b11;
	uint32 sysClk = HSI;
	switch (SW) {
	case 0:
		sysClk = HSI;
		break;
	case 1:
		//todo need to calculate  it //HSE User Should Specify it
		sysClk = HSE;
		break;
	case 2:
		uint8 pll_src = (RCC->CFGR >> 16) & 1 ;
		if(pll_src){ // HSE
			 sysClk = GET(RCC->CFGR,17) == 1 ?( HSE /2) : HSE ; //check if HSE is divided by 2
		}else{ //HSI / 2 = 4MHZ
			sysClk = HSI/2 ;
		}
		uint16 pll_mul = (RCC->CFGR >> 18) & 0b1111;
		sysClk = sysClk * (pll_mul+2);
		break;

	}
	return sysClk;
}

uint32 RCC_getPCKL1_Freq(void) {
	/* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
	return (RCC_getHCKL_Freq() >> APB_PrescTable[((RCC->CFGR >> 8) & 0b111)]); // First right shift is multiplication
}
uint32 RCC_getPCKL2_Freq(void) {
	/* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
	return (RCC_getHCKL_Freq() >> APB_PrescTable[((RCC->CFGR >> 11) & 0b111)]);
}
uint32 RCC_getHCKL_Freq(void) {
	/* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
	return (RCC_getSYSCLK_Freq() >> AHB_PrescTable[((RCC->CFGR >> 4) & 0b1111)]);
}

void RCC_init(RCC_CLKSrc_t clkSrc, RCC_HSESrc_t HSESrc, RCC_PLLSrc_t PLLSrc,
		uint8 PLLMUL) {
	switch (clkSrc) {
	case RCC_HSI:
		/*
		 *  HSION: Internal high-speed clock enable
		 */
		RCC->CR |= (1 << 0);
		// choose src
		RCC->CFGR &= ~(1 << 0);
		RCC->CFGR &= ~(1 << 1);
		break;
	case RCC_HSE:
		/* Enable HSEON
		 * 0: HSE oscillator OFF
		 * 1: HSE oscillator ON
		 */
		RCC->CR |= (1 << 16);
		switch (HSESrc) {
		case HSE_CRYSTAL:
			// disable bypass
			RCC->CR &= ~(1 << 18);
			// choose src
			RCC->CFGR |= (1 << 0);
			RCC->CFGR &= ~(1 << 1);
			break;
		case HSE_RC:
			// enable bypass
			RCC->CR |= (1 << 18);
			// choose src
			RCC->CFGR |= (1 << 0);
			RCC->CFGR &= ~(1 << 1);
			break;
		}
		break;
	case RCC_PLL:
		switch (PLLSrc) {
		case PLL_HSE:
			/**
			 * PLLSRC: PLL entry clock source
			 Set and cleared by software to select PLL clock source. This bit can be written only when
			 PLL is disabled.
			 0: HSI oscillator clock / 2 selected as PLL input clock
			 1: HSE oscillator clock selected as PLL input clock
			 */
			RCC->CFGR |= (1 << 16);
			/*
			 * PLLXTPRE: HSE divider for PLL entry
			 0: HSE clock not divided
			 1: HSE clock divided by 2
			 */
			RCC->CFGR &= ~(1 << 17);
			// SET PLL MUL
			RCC->CFGR |= (PLLMUL << 18);
			// 24 PLLON: PLL enable
			RCC->CR |= (1 << 24);
			/* Enable HSEON
			 * 0: HSE oscillator OFF
			 * 1: HSE oscillator ON
			 */
			RCC->CR |= (1 << 16);
			RCC->CFGR &= ~(1 << 0);
			RCC->CFGR |= (1 << 1);
			break;
		case PLL_HSI:
			/*
			 *  HSION: Internal high-speed clock enable
			 */
			RCC->CR |= (1 << 0);
			// SET PLL MUL
			RCC->CFGR |= (PLLMUL << 18);
			// 24 PLLON: PLL enable
			RCC->CR |= (1 << 24);

			RCC->CFGR &= ~(1 << 0);
			RCC->CFGR |= (1 << 1);

			RCC->CFGR &= ~(1 << 16);

			break;
		}
		break;

	}
}

void RCC_CLK_EN(uint8 busID, uint8 periphralID) {
	switch (busID) {
	case APB1_ID:
		RCC->ABP1ENR |= (1 << periphralID);
		break;
	case APB2_ID:
		RCC->ABP2ENR |= (1 << periphralID);
		break;
	case AHB_ID:
		RCC->AHBENR |= (1 << periphralID);
		break;
	}
}

void RCC_CLK_RST(uint8 busID, uint8 periphralID) {
	switch (busID) {
	case APB1_ID:
		RCC->ABP1ENR |= (1 << periphralID);
		break;
	case APB2_ID:
		RCC->ABP1ENR |= (1 << periphralID);
		break;
	case AHB_ID:
		RCC->AHBENR &= ~(1 << periphralID);
		break;
	}
}
void RCC_setAPB1Prescalar(APB_Prescalar_t prescalar) {
	RCC->CFGR |= (prescalar << 8);
}
void RCC_setAPB2Prescalar(APB_Prescalar_t prescalar) {
	RCC->CFGR |= (prescalar << 11);

}
void RCC_setAHBPrescalar(AHB_Prescalar_t prescalar) {
	RCC->CFGR |= (prescalar << 4);
}

void RCC_setADCPrescalar(int prescalar) {
	RCC->CFGR |= (prescalar << 14);
}
