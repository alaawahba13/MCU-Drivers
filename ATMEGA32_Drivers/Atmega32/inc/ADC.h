/*
 * ADC.h
 *
 *  Created on: 10 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef ATMEGA32_INC_ADC_H_
#define ATMEGA32_INC_ADC_H_

//-----------------------------
//Includes
//-----------------------------
#include "Atmega32.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/Platform_types.h"


//-----------------------------
// Configuration Refrences
//-----------------------------
#define MAX_timeout 		50000
typedef enum{
	AREF = 0x00,
	VCC_5 = 0x40,
	VCC_2_56= 0xC0
}ADC_VREF_t;

typedef enum{
	RIGHT=0x00,
	LEFT=0x20
}ADC_ADJUST_t;

typedef enum{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
}ADC_CHANNEL_t;

typedef enum{
	PRESCALAR_2=0,
	PRESCALAR_4 = 2,
	PRESCALAR_8,
	PRESCALAR_16,
	PRESCALAR_32,
	PRESCALAR_64,
	PRESCALAR_128,
}ADC_PRESCALAR_t;

typedef enum{
	DISABLE ,
	ENABLE
}ADC_EN_t;

typedef enum{
	SINGLE_CONVERSION=0x00,
	FREE_RUNNING=0x20,
}ADC_MODE_t;

typedef struct{
	ADC_VREF_t vref;
	ADC_ADJUST_t adjust;
	ADC_PRESCALAR_t prescalar;
	ADC_EN_t INT_Enable;
	ADC_MODE_t mode;
	void (*CallBack_Ptr)(void);
}ADC_pinConfig_t;

/*
* ===============================================
* APIs Supported by "ADC DRIVER"
* ===============================================
*/

void ADC_init(ADC_pinConfig_t *pin_Config);
void ADC_Deinit();

uint16 ADC_Read(ADC_CHANNEL_t ADCx);
#endif /* ATMEGA32_INC_ADC_H_ */
