/*
 * WDT.c
 *
 *  Created on: 2 Aug 2023
 *      Author:  Alaa Wahba
 */


#include "WDT.h"

/**================================================================
 * @Fn				- WDT_Enable
 * @brief 			- Initializes the watchdog timer according to the specified time out.
 * @param [in]	    - prescalar : specifies the watch dog time out @ref prescalar_define
 * @retval 			- none
 */

void WDT_Enable(uint8 prescalar){

   WDTCR = prescalar;
   SET(WDTCR,WDE);
}

void WDT_Disable(){
	/* the same operation, write a logic one to WDTOE and WDE.
	 * A logic one must be written to WDE even though it is set to one before the disable operation starts.
	 */
	WDTCR = (1<<WDE) | (1<<WDTOE);
// Within the next four clock cycles, write a logic 0 to WDE. This disables the Watchdog.
	WDTCR = 0x00;
}

