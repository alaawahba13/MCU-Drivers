/*
 * ADC.h
 *
 *  Created on: 6 Feb 2024
 *      Author: Alaa Wahba
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_
//=======================
//       Includes
//=======================

#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"

//================================================
//   User type definitions (structures)
//================================================
// This struct is not used and to be completed in the future
typedef struct{
	uint8 Conversion_Mode; //Single or continous
	uint8 Data_Alignment;
	uint8 ADC_Group; // injected or regular
	uint8 DualMode;
}ADC_pinConfig_t;


//===============================================
//      Macros Configuration References
//===============================================

/*
 * @ref ADC_CHx
 */
typedef enum{
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
	ADC_CH8,
	ADC_CH9,
	ADC_CH10,
	ADC_CH11,
	ADC_CH12,
	ADC_CH13,
	ADC_CH14,
	ADC_CH15,
}ADC_CHANNEL_t;

/*
 * @ref Data_Alignment
 */
#define RIGHT_ALIGN  (uint32)(0)
#define LEFT_ALIGN 	 (uint32)(1<<11)

/*
 * @ref DualMode
 */
typedef enum{
	 Independent_mode = 0x0000,
	 regular_injected,
	 regular_alternateTrigger,
	 injected_fastInterleaved,
	 injected_slowInterleaved,
	 injected,
	 regular,
	 fastInterleaved,
	 slowInterleaved,
	 alternateTrigger
}ADC_DualMode_t;



/*
* ===============================================
*      APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

void ADC_init(ADC_Registers_t* ADCx);
uint16 ADC_read( ADC_Registers_t* ADCx, ADC_CHANNEL_t ADC_CHx);




#endif /* ADC_ADC_H_ */
