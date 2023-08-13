/*
 * ADC.c
 *
 *  Created on: 10 Aug 2023
 *      Author: Alaa Wahba
 */

#include "ADC.h"

void (*G_CallBack)(void);
ADC_pinConfig_t G_pinConfig;
uint16 data;

void ADC_init(ADC_pinConfig_t *pin_Config) {
	G_pinConfig = *pin_Config;
	ADMUX |= pin_Config->vref;
	ADMUX |= pin_Config->adjust;

	if (pin_Config->mode == FREE_RUNNING)
		SET(ADCSRA, ADATE);

	ADCSRA |= pin_Config->prescalar;

	SET(ADCSRA, ADEN);

}
void ADC_Deinit() {
	ADMUX = 0x00;
	ADCSRA = 0x00;

}
uint16 ADC_Read(ADC_CHANNEL_t ADCx) {

	uint8 timeout = 0;
	//Select Channel
	ADMUX &= 0xE0;
	ADMUX |= ADCx;
	//Start conversion
	SET(ADCSRA, ADSC);
	if (G_pinConfig.INT_Enable == DISABLE) {
		//Wait
		while ((!GET(ADCSRA, ADSC)) && (timeout < MAX_timeout)) {
			timeout++;
		}
		if (GET(ADCSRA, ADSC)) {
			if (G_pinConfig.adjust == RIGHT)
				data = ADC;
			else
				data = ADC >> 6;
		}
	} else {
		SET(ADCSRA, ADIE);
		G_CallBack = G_pinConfig.CallBack_Ptr;
	}

	return data;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void) {
	if (G_pinConfig.adjust == RIGHT)
		data = ADC;
	else
		data = ADC >> 6;
	G_CallBack();
}
