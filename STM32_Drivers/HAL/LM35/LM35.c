/*
 * LM35.c
 *
 *  Created on: 17 Feb 2024
 *      Author: Alaa
 */


#include "LM35.h"

void LM35_init(ADC_Registers_t* ADCx){
	ADC_init(ADCx);
}
uint16 LM35_Read(ADC_Registers_t* ADCx,ADC_CHANNEL_t CHx){
	uint16 data = ADC_read(ADCx, CHx);

	/*
	 *data >>> mvolt
	  4095 >>> 3300
	 */
	uint16 mV = (data*3300)/4095;
	uint16 temp = mV/10;
	return temp;
}
