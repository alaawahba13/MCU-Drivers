/*
 * ADC.c
 *
 *  Created on: 6 Feb 2024
 *      Author: Alaa Wahba
 */

//=======================
//       Includes
//=======================
#include "ADC.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
static ADC_pinConfig_t Global_pinConfig[3] = { 0, 0, 0 };

#define ADC1_Index 			0
#define ADC2_Index 			1
#define ADC3_Index 			2

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

// single conversion mode only
void ADC_init(ADC_Registers_t *ADCx) {

	//1. Enable ADC clock
	if (ADCx == ADC1) {
		RCC_CLK_EN(APB2_ID, ADC1_ID);
	} else if (ADCx == ADC2) {
		RCC_CLK_EN(APB2_ID, ADC2_ID);
	} else if (ADCx == ADC3) {
		RCC_CLK_EN(APB2_ID, ADC3_ID);
	}

	    ADCx->CR2 |= (1 << 0); // Enable ADC (ADON bit)


}

uint16 ADC_read(ADC_Registers_t *ADCx, ADC_CHANNEL_t ADC_CHx) {
	GPIO_PinConfig_t GPIO_pinConfig;
	GPIO_pinConfig.MODE = MODE_Analog;
	 /*channels from 10 to 17*/
	    if (ADC_CHx > ADC_CH9)
	    {
	        /* Clear the old channel sample time */
	    	ADCx->SMPR1 &= 0x7 << (3 * (ADC_CHx - 10));
	        /* Set the new channel sample time */
	        ADCx->SMPR1 |= (uint32)(0b11) << (3 * (ADC_CHx - 10));
	    }
	    else /*channels from 0 to 9 */
	    {
	        /* Clear the old channel  */
	    	ADCx->SMPR2 &= 0x7 << (3 * ADC_CHx);
	        /* Set the new channel */
	    	ADCx->SMPR2 |= (uint32)(0b11) << (3 * ADC_CHx);
	    }
	switch (ADC_CHx) {
	case ADC_CH0:
		// configure PA0 as analog
		RCC_CLK_EN(APB2_ID, GPIOA_ID);
		GPIO_pinConfig.Pin_Number = PIN_0;
		GPIO_init(GPIOA, &GPIO_pinConfig);
		break;
	case ADC_CH1:
			// configure PA1 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_1;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH2:
			// configure PA2 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_2;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH3:
			// configure PA3 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_3;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH4:
			// configure PA4 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_4;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH5:
			// configure PA5 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_5;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH6:
			// configure PA6 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_6;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH7:
			// configure PA7 as analog
			RCC_CLK_EN(APB2_ID, GPIOA_ID);
			GPIO_pinConfig.Pin_Number = PIN_7;
			GPIO_init(GPIOA, &GPIO_pinConfig);
			break;
	case ADC_CH8:
			// configure PB0 as analog
			RCC_CLK_EN(APB2_ID, GPIOB_ID);
			GPIO_pinConfig.Pin_Number = PIN_0;
			GPIO_init(GPIOB, &GPIO_pinConfig);
			break;
	case ADC_CH9:
			// configure PB1 as analog
			RCC_CLK_EN(APB2_ID, GPIOB_ID);
			GPIO_pinConfig.Pin_Number = PIN_1;
			GPIO_init(GPIOB, &GPIO_pinConfig);
			break;
	case ADC_CH10:
			// configure PC0 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_0;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	case ADC_CH11:
			// configure PC1 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_1;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	case ADC_CH12:
			// configure PC2 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_2;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	case ADC_CH13:
			// configure PC3 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_3;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	case ADC_CH14:
			// configure PC4 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_4;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	case ADC_CH15:
			// configure PC5 as analog
			RCC_CLK_EN(APB2_ID, GPIOC_ID);
			GPIO_pinConfig.Pin_Number = PIN_5;
			GPIO_init(GPIOC, &GPIO_pinConfig);
			break;
	}
	//2. Enable ADC
    ADCx->SQR[0] |= ((ADC_CHx - (uint8) 1) << 20);
    ADCx->SQR[2] = (ADCx->SQR[2] & ~(0x1F)) | ADC_CHx;

	//start conversion
    ADCx->CR2 |= (1 << 0);
    ADCx->CR2 |= (1 << 22);

	//wait for EOC Flag to be set
	while(!(ADCx->SR & (1<<1)));

	// read data
	return (ADCx->DR);
}
