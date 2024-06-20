/*
 * LM35.h
 *
 *  Created on: 17 Feb 2024
 *      Author: Alaa
 */

#ifndef LM35_LM35_H_
#define LM35_LM35_H_

#include "../../MCAL/ADC/ADC.h"

void LM35_init(ADC_Registers_t* ADCx);
uint16 LM35_Read(ADC_Registers_t* ADCx,ADC_CHANNEL_t CHx);

#endif /* LM35_LM35_H_ */
