/*
 * NVIC.c
 *
 *  Created on: 20 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef NVIC_C_
#define NVIC_C_

//=======================
//       Includes
//=======================
#include "NVIC.h"

/**================================================================
 * @Fn             - NVIC_Enable
 * @brief          - Enables the NVIC interrupt pin
 * @param [in]     - IRQ_Number :  The specified Interrupt Number to be enabled
 * @retval         - none
 */

void NVIC_Enable(uint8 IRQ_Number) {
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
		ISER0 |= (1U << IRQ_Number);
	} else if ((IRQ_Number >= 32) && (IRQ_Number <= 59)) {
		ISER1 |= (1U << (IRQ_Number - 32));
	}
}

/**================================================================
 * @Fn             - NVIC_Disable
 * @brief          - Disables the NVIC interrupt pin
 * @param [in]     - IRQ_Number :  The specified Interrupt Number to be disabled
 * @retval         - none
 */

void NVIC_Disable(uint8 IRQ_Number) {
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
		ICER0 |= (1U << IRQ_Number);
	} else if ((IRQ_Number >= 32) && (IRQ_Number <= 59)) {
		ICER1 |= (1U << (IRQ_Number - 32));
	}
}

/**================================================================
 * @Fn             - NVIC_setPending
 * @brief          - Force interrupts into the pending state.
 * @param [in]     - IRQ_Number :  The specified Interrupt Number
 * @retval         - none
 */

void NVIC_setPending(uint8 IRQ_Number) {
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
		ISPR0 |= (1U << IRQ_Number);
	} else if ((IRQ_Number >= 32) && (IRQ_Number <= 59)) {
		ISPR1 |= (1U << (IRQ_Number - 32));
	}
}

/**================================================================
 * @Fn             - NVIC_clearPending
 * @brief          - Registers remove the pending state from interrupts
 * @param [in]     - IRQ_Number :  The specified Interrupt Number
 * @retval         - none
 */

void NVIC_clearPending(uint8 IRQ_Number) {
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
		ICPR0 |= (1U << IRQ_Number);
	} else if ((IRQ_Number >= 32) && (IRQ_Number <= 59)) {
		ICPR1 |= (1U << (IRQ_Number - 32));
	}
}

/**================================================================
 * @Fn             - NVIC_getActiveBit
 * @brief          - Indicate which interrupts are active.
 * @param [in]     - IRQ_Number :  The specified Interrupt Number
 * @retval         - ret_val: 1 if the interrupt is active, 0 else.
 */

uint8 NVIC_getActiveBit(uint8 IRQ_Number) {
	uint8 ret_val = 0U;
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
		ret_val = GET(IABR0, IRQ_Number);
	} else if ((IRQ_Number >= 32) && (IRQ_Number <= 59)) {
		ret_val = GET(IABR1, (IRQ_Number - 32));
	}
	return ret_val;
}
/**================================================================
 * @Fn             - NVIC_setPriority
 * @brief          - Indicate which interrupts are active.
 * @param [in]     - IRQ_Number :  The specified Interrupt Number
 * @retval         - ret_val: 1 if the interrupt is active, 0 else.
 */

void NVIC_setPriority(NVIC_Group_Sub_t bitNum, uint8 subPriority,
		uint8 groupPriority, uint8 intNum) {
	/*
	 * IPR index is periphral ID from vector table
	 * IPR higher four bits are set to group priority and sub priority according to bitNum
	 */
	if ((intNum >= 0) && (intNum <= 59)) {
		IPR[0] = ((subPriority  | (groupPriority << ((bitNum - _4G_0S)/256))) << 4); // divide by 256 to wrap the decimal value
																					 // shifting by four since only higher 4 bits are used

	}
	SCB_AIRCR = bitNum;

}

#endif /* NVIC_C_ */
