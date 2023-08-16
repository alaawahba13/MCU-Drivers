/*
 * LM35.c
 *
 *  Created on: 16 Aug 2023
 *      Author: Alaa Wahba
 */

#include "LM35.h"


void LM35_init(){
	ADC_pinConfig_t ADC_pinConfig ={VCC_5, RIGHT, PRESCALAR_64, DISABLE,SINGLE_CONVERSION ,NULL };
	ADC_init(&ADC_pinConfig);

}

uint32 LM35_getTemperature(){
	uint16 val;
	uint32 Temp;
	val = ADC_Read(ADCx);
	Temp = (((uint32) val) * 500) / 1024;
	return Temp;
}
