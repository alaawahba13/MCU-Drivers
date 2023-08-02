/*
 * WDT.h
 *
 *  Created on: 2 Aug 2023
 *      Author:  Alaa Wahba
 */

#ifndef ATMEGA32_INC_WDT_H_
#define ATMEGA32_INC_WDT_H_

//=======================
//Includes
//=======================

#include "Atmega32.h"
#include "util/delay.h"
#include "../../Library/BIT_MATH.h"

//=======================
//Macros
//=======================
/*
 * @ ref prescalar_define
 */

#define WDT_16_3_ms				0
#define WDT_32_5_ms				1
#define WDT_65_ms				2
#define WDT_130_ms				3
#define WDT_260_ms				4
#define WDT_520_ms				5
#define WDT_1000_ms				6
#define WDT_2100_ms				7



/*
* ===============================================
* APIs Supported by "MCAL WDT DRIVER"
* ===============================================
*/

void WDT_Enable(uint8 prescalar);
void WDT_Disable();



#endif /* ATMEGA32_INC_WDT_H_ */
