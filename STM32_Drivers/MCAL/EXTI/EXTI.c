/*
 * EXTI.c
 *
 *  Created on: 30 Jan 2023
 *      Author: Alaa Wahba
 */

//=======================
//       Includes
//=======================
#include "EXTI.h"


//=================================
//       Generic Variables
//=================================
void (*GP_Fun[16])(void);
//=================================
//       IRQ Handlers
//=================================
void EXTI0_IRQHandler() {
	EXTI->PR |= (1 << 0);
	GP_Fun[0]();
}
void EXTI1_IRQHandler() {
	EXTI->PR |= (1 << 1);
	GP_Fun[1]();
}
void EXTI2_IRQHandler() {
	EXTI->PR |= (1 << 2);
	GP_Fun[2]();
}
void EXTI3_IRQHandler() {
	EXTI->PR |= (1 << 3);
	GP_Fun[3]();
}
void EXTI4_IRQHandler() {
	EXTI->PR |= (1 << 4);
	GP_Fun[4]();
}
void EXTI9_5_IRQHandler() {
	if (EXTI->PR & (1 << 5)) {
		EXTI->PR |= (1 << 5);
		GP_Fun[5]();
	} else if (EXTI->PR & (1 << 6)) {
		EXTI->PR |= (1 << 6);
		GP_Fun[6]();
	} else if (EXTI->PR & (1 << 7)) {
		EXTI->PR |= (1 << 7);
		GP_Fun[7]();
	} else if (EXTI->PR & (1 << 8)) {
		EXTI->PR |= (1 << 8);
		GP_Fun[8]();
	} else if (EXTI->PR & (1 << 9)) {
		EXTI->PR |= (1 << 9);
		GP_Fun[9]();
	}
}
void EXTI15_10_IRQHandler() {
	if (EXTI->PR & (1 << 10)) {
		EXTI->PR |= (1 << 10);
		GP_Fun[10]();
	} else if (EXTI->PR & (1 << 11)) {
		EXTI->PR |= (1 << 11);
		GP_Fun[11]();
	} else if (EXTI->PR & (1 << 12)) {
		EXTI->PR |= (1 << 12);
		GP_Fun[12]();
	} else if (EXTI->PR & (1 << 13)) {
		EXTI->PR |= (1 << 13);
		GP_Fun[13]();
	} else if (EXTI->PR & (1 << 14)) {
		EXTI->PR |= (1 << 14);
		GP_Fun[14]();
	} else if (EXTI->PR & (1 << 15)) {
		EXTI->PR |= (1 << 15);
		GP_Fun[15]();
	}

}
/*
 * ================================
 *      Generic Functions
 * ================================
 */

/**================================================================
 * @Fn				- Update_EXTI
 * @brief 			- Updates the specified EXTI pin
 * @param [in]	    - pinConfig :  pointer to a structure that contains the pin configuration information
 * 								   Must be initialized from @ref  EXTI_Mapping , @ref EXTI_Trigger_define ,@ref EXTI_Enable_define
 * @retval 			- none
 */

void Update_EXTI(EXTI_PinConfig_t *pinConfig) {
	/*
	 * 1. Pin Must be configured as floating input
	 * 2. Configure the selected port using AFIO_EXTIx registers
	 * 3. Configure Trigger edge
	 * 4. Enable Mask Bit
	 * 5. Enable the IRQ in interrupt controller NVIC
	 * 6. Call the IRQ Handler
	 */
	//1
	GPIO_PinConfig_t GPIO_pinConfig;
	GPIO_pinConfig.Pin_Number = pinConfig->pinMapping.pinNumber;
	GPIO_pinConfig.MODE = MODE_INPUT_FLO;
	GPIO_Registers_t *GPIO_Port = pinConfig->pinMapping.GPIO;
	uint16 EXTI_LineNumber = (uint16) pinConfig->pinMapping.lineNumber;

	GPIO_init(GPIO_Port, &GPIO_pinConfig);
	//2
	uint8 AFIO_Shift = (EXTI_LineNumber % 4) * 4;
	uint8 AFIO_index = (EXTI_LineNumber / 4); //specifies which AFIO_EXTICRx register to use
	uint8 portMask;								// values from TRM
	if (GPIO_Port == GPIOA)
		portMask = PA;
	else if (GPIO_Port == GPIOB)
		portMask = PB;
	else if (GPIO_Port == GPIOC)
		portMask = PC;
	else if (GPIO_Port == GPIOD)
		portMask = PD;

	AFIO->EXTICR[AFIO_index] &= ~(0xF << AFIO_Shift);
	AFIO->EXTICR[AFIO_index] |= (portMask << AFIO_Shift);

	//3
	EXTI->RTSR &= ~(1 << EXTI_LineNumber);
	EXTI->FTSR &= ~(1 << EXTI_LineNumber);


	if (pinConfig->triggerEdge == EXTI_Rising_edge) {
		EXTI->RTSR |= (1 << EXTI_LineNumber);
	} else if (pinConfig->triggerEdge == EXTI_Falling_edge) {
		EXTI->FTSR |= (1 << EXTI_LineNumber);
	} else if(pinConfig->triggerEdge == EXTI_BOTH_edges){
		EXTI->RTSR |= (1 << EXTI_LineNumber);
		EXTI->FTSR |= (1 << EXTI_LineNumber);
	}
	// 6
	GP_Fun[EXTI_LineNumber] = pinConfig->P_Fun;
	// 4 , 5
	if (pinConfig->IRQ_Enable == EXTI_IRQ_Enabled) {
		EXTI->IMR |= (1 << EXTI_LineNumber);
		NVIC_Enable(pinConfig->pinMapping.IVT_IRQ_Number);
	} else if (pinConfig->IRQ_Enable == EXTI_IRQ_Disabled) {
		EXTI->IMR &= ~(1 << EXTI_LineNumber);
		NVIC_Disable(pinConfig->pinMapping.IVT_IRQ_Number);
	}

}

/**================================================================
 * @Fn				- NVIC_Enable
 * @brief 			- Enables the NVIC interrupt pin
 * @param [in]	    - IRQ_Number :  The specified Interrupt Number to be enabled
 * @retval 			- none
 */

void NVIC_Enable(uint8 IRQ_Number) {
	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
	 NVIC_ISER->ISER0 |= (1 << IRQ_Number);
	 } else if ((IRQ_Number >= 32) && (IRQ_Number <= 63)) {
	 NVIC_ISER->ISER1 |= (1 << (IRQ_Number-32));
	 } else if ((IRQ_Number >= 64) && (IRQ_Number <= 67)) {
	 NVIC_ISER->ISER2 |= (1 << (IRQ_Number-32));
	 }
}
/**================================================================
 * @Fn				- NVIC_Disable
 * @brief 			- Disables the NVIC interrupt pin
 * @param [in]	    - IRQ_Number :  The specified Interrupt Number to be disabled
 * @retval 			- none
 */

void NVIC_Disable(uint8 IRQ_Number) {

	if ((IRQ_Number >= 0) && (IRQ_Number <= 31)) {
	 NVIC_ICER->ICER0 |= (1 << IRQ_Number);
	 } else if ((IRQ_Number >= 32) && (IRQ_Number <= 63)) {
	 NVIC_ICER->ICER1 |= (1 << (IRQ_Number-32));
	 } else if ((IRQ_Number >= 64) && (IRQ_Number <= 67)) {
	 NVIC_ICER->ICER2 |= (1 << (IRQ_Number-32));
	 }

}

/*
 * ===============================================
 *      APIs Supported by "MCAL EXTI DRIVER"
 * ===============================================
 */

/**================================================================
 * @Fn				- EXTI_Init
 * @brief 			- Initializes the specified pin as External Interrupt
 * @param [in]	    - pinConfig :  pointer to a structure that contains the pin configuration information
 * 								   Must be initialized from @ref  EXTI_Mapping , @ref EXTI_Trigger_define ,@ref EXTI_Enable_define
 * @retval 			- none
 */

void EXTI_init(EXTI_PinConfig_t *pinConfig) {
	Update_EXTI(pinConfig);
}
void EXTI_Update(EXTI_PinConfig_t *pinConfig) {
	Update_EXTI(pinConfig);

}
/**================================================================
 * @Fn				- EXTI_DeInit
 * @brief 			- reset all the EXTI registers
 * @param [in]	    - void
 * @retval 			- none
 */

void EXTI_deInit(void) {

	// Reset all EXTI registers using reset values from TRM
	EXTI->EMR = 0x0000;
	EXTI->FTSR = 0x0000;
	EXTI->IMR = 0x0000;
	EXTI->RTSR = 0x0000;
	EXTI->SWIER = 0x0000;
	EXTI->PR = 0xFFFF;
	// Reset NVIC Registers
	NVIC_Disable(EXTI_IRQ_0);
	NVIC_Disable(EXTI_IRQ_1);
	NVIC_Disable(EXTI_IRQ_2);
	NVIC_Disable(EXTI_IRQ_3);
	NVIC_Disable(EXTI_IRQ_4);
	NVIC_Disable(EXTI_IRQ_5);
	NVIC_Disable(EXTI_IRQ_10);

}

