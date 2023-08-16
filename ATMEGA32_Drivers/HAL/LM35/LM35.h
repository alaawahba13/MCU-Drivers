/*
 * LM35.h
 *
 *  Created on: 16 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef LM35_LM35_H_
#define LM35_LM35_H_

#include "../../Atmega32/inc/ADC.h"

#define ADCx 			ADC3

void LM35_init();
uint32 LM35_getTemperature();


#endif /* LM35_LM35_H_ */
