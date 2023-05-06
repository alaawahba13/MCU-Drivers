/*
 * RCC.h
 *
 *  Created on: 16 Feb 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
//=======================
//       Includes
//=======================
#include "STM32_F103x6.h"

#define HSI 		(uint32)8000000
#define HSE 		(uint32)16000000
/*
* ===============================================
*      APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/
uint32 RCC_getSYSCLK_Freq(void);

uint32 RCC_getPCKL1_Freq(void);
uint32 RCC_getPCKL2_Freq(void);
uint32 RCC_getHCKL_Freq(void);


#endif /* INC_RCC_H_ */
