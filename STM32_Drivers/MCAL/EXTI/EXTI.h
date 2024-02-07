/*
 * EXTI.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

//=======================
//       Includes
//=======================

#include "../GPIO/GPIO.h"
#include "../NVIC/NVIC.h"


//================================================
//   User type definitions (structures)
//================================================

typedef struct {
	/*
	 * Inputs to EXTI
	 1. PIN NUMBER 		0-15
	 2. LINE NUMBER 	0-15
	 3. IVT IRQ NUMBER 	According to TRM
	 4. PORT
	 */
	uint16 pinNumber;
	uint16 lineNumber;
	GPIO_Registers_t *GPIO;
	uint8 IVT_IRQ_Number;

} EXTI_Mapping_t;

/*
	 *  PinConfig
	 1. INPUTS
	 2. Trigger edge
	 3. Enable
	 4. Function
	 */
typedef struct {

	/*
	 *  Specifies The EXTI GPIO Mapping
	 *  Must be initialized based on @ref EXTI_Mapping
	 */
	EXTI_Mapping_t pinMapping; /*
	 *  Specifies The EXTI GPIO Mapping
	 *  Must be initialized based on @ref EXTI_Mapping
	 */
	uint8 triggerEdge; /*
	 * Specifies Interrupt Trigger : Falling / Rising edge
	 *  Must be initialized based on @ref EXTI_Trigger_define
	 */
	uint8 IRQ_Enable; /*
	 * Specifies Interrupt 	Enable / Mask pin
	 *  Must be initialized based on @ref EXTI_Enable_define
	 */
	void (*P_Fun)(void);// The C function() that is called when IRQ is enabled.
} EXTI_PinConfig_t;
//===============================================
//      Macros Configuration References
//===============================================

//@ref EXTI_Mapping
#define EXTI0PA0         (EXTI_Mapping_t){PIN_0, EXTI0, GPIOA, NVIC_EXTI0}
#define EXTI0PB0         (EXTI_Mapping_t){PIN_0, EXTI0, GPIOB, NVIC_EXTI0}
#define EXTI0PC0         (EXTI_Mapping_t){PIN_0, EXTI0, GPIOC, NVIC_EXTI0}
#define EXTI0PD0         (EXTI_Mapping_t){PIN_0, EXTI0, GPIOD, NVIC_EXTI0}

#define EXTI1PA1         (EXTI_Mapping_t){PIN_1, EXTI1, GPIOA, NVIC_EXTI1}
#define EXTI1PB1         (EXTI_Mapping_t){PIN_1, EXTI1, GPIOB, NVIC_EXTI1}
#define EXTI1PC1         (EXTI_Mapping_t){PIN_1, EXTI1, GPIOC, NVIC_EXTI1}
#define EXTI1PD1         (EXTI_Mapping_t){PIN_1, EXTI1, GPIOD, NVIC_EXTI1}

#define EXTI2PA2         (EXTI_Mapping_t){PIN_2, EXTI2, GPIOA, NVIC_EXTI2}
#define EXTI2PB2         (EXTI_Mapping_t){PIN_2, EXTI2, GPIOB, NVIC_EXTI2}
#define EXTI2PC2         (EXTI_Mapping_t){PIN_2, EXTI2, GPIOC, NVIC_EXTI2}
#define EXTI2PD2         (EXTI_Mapping_t){PIN_2, EXTI2, GPIOD, NVIC_EXTI2}

#define EXTI3PA3         (EXTI_Mapping_t){PIN_3, EXTI3, GPIOA, NVIC_EXTI3}
#define EXTI3PB3         (EXTI_Mapping_t){PIN_3, EXTI3, GPIOB, NVIC_EXTI3}
#define EXTI3PC3         (EXTI_Mapping_t){PIN_3, EXTI3, GPIOC, NVIC_EXTI3}
#define EXTI3PD3         (EXTI_Mapping_t){PIN_3, EXTI3, GPIOD, NVIC_EXTI3}

#define EXTI4PA4         (EXTI_Mapping_t){PIN_4, EXTI4, GPIOA, NVIC_EXTI4}
#define EXTI4PB4         (EXTI_Mapping_t){PIN_4, EXTI4, GPIOB, NVIC_EXTI4}
#define EXTI4PC4         (EXTI_Mapping_t){PIN_4, EXTI4, GPIOC, NVIC_EXTI4}
#define EXTI4PD4         (EXTI_Mapping_t){PIN_4, EXTI4, GPIOD, NVIC_EXTI4}

#define EXTI5PA5         (EXTI_Mapping_t){PIN_5, EXTI5, GPIOA, NVIC_EXTI5}
#define EXTI5PB5         (EXTI_Mapping_t){PIN_5, EXTI5, GPIOB, NVIC_EXTI5}
#define EXTI5PC5         (EXTI_Mapping_t){PIN_5, EXTI5, GPIOC, NVIC_EXTI5}
#define EXTI5PD5         (EXTI_Mapping_t){PIN_5, EXTI5, GPIOD, NVIC_EXTI5}

#define EXTI6PA6         (EXTI_Mapping_t){PIN_6, EXTI6, GPIOA, NVIC_EXTI6}
#define EXTI6PB6         (EXTI_Mapping_t){PIN_6, EXTI6, GPIOB, NVIC_EXTI6}
#define EXTI6PC6         (EXTI_Mapping_t){PIN_6, EXTI6, GPIOC, NVIC_EXTI6}
#define EXTI6PD6         (EXTI_Mapping_t){PIN_6, EXTI6, GPIOD, NVIC_EXTI6}

#define EXTI7PA7         (EXTI_Mapping_t){PIN_7, EXTI7, GPIOA, NVIC_EXTI7}
#define EXTI7PB7         (EXTI_Mapping_t){PIN_7, EXTI7, GPIOB, NVIC_EXTI7}
#define EXTI7PC7         (EXTI_Mapping_t){PIN_7, EXTI7, GPIOC, NVIC_EXTI7}
#define EXTI7PD7         (EXTI_Mapping_t){PIN_7, EXTI7, GPIOD, NVIC_EXTI7}

#define EXTI8PA8         (EXTI_Mapping_t){PIN_8, EXTI8, GPIOA, NVIC_EXTI8}
#define EXTI8PB8         (EXTI_Mapping_t){PIN_8, EXTI8, GPIOB, NVIC_EXTI8}
#define EXTI8PC8         (EXTI_Mapping_t){PIN_8, EXTI8, GPIOC, NVIC_EXTI8}
#define EXTI8PD8         (EXTI_Mapping_t){PIN_8, EXTI8, GPIOD, NVIC_EXTI8}

#define EXTI9PA9         (EXTI_Mapping_t){PIN_9, EXTI9, GPIOA, NVIC_EXTI9}
#define EXTI9PB9         (EXTI_Mapping_t){PIN_9, EXTI9, GPIOB, NVIC_EXTI9}
#define EXTI9PC9         (EXTI_Mapping_t){PIN_9, EXTI9, GPIOC, NVIC_EXTI9}
#define EXTI9PD9         (EXTI_Mapping_t){PIN_9, EXTI9, GPIOD, NVIC_EXTI9}

#define EXTI10PA10       (EXTI_Mapping_t){PIN_10, EXTI10, GPIOA, NVIC_EXTI10}
#define EXTI10PB10       (EXTI_Mapping_t){PIN_10, EXTI10, GPIOB, NVIC_EXTI10}
#define EXTI10PC10       (EXTI_Mapping_t){PIN_10, EXTI10, GPIOC, NVIC_EXTI10}
#define EXTI10PD10       (EXTI_Mapping_t){PIN_10, EXTI10, GPIOD, NVIC_EXTI10}

#define EXTI11PA11       (EXTI_Mapping_t){PIN_11, EXTI11, GPIOA, NVIC_EXTI11}
#define EXTI11PB11       (EXTI_Mapping_t){PIN_11, EXTI11, GPIOB, NVIC_EXTI11}
#define EXTI11PC11       (EXTI_Mapping_t){PIN_11, EXTI11, GPIOC, NVIC_EXTI11}
#define EXTI11PD11       (EXTI_Mapping_t){PIN_11, EXTI11, GPIOD, NVIC_EXTI11}

#define EXTI12PA12       (EXTI_Mapping_t){PIN_12, EXTI12, GPIOA, NVIC_EXTI12}
#define EXTI12PB12       (EXTI_Mapping_t){PIN_12, EXTI12, GPIOB, NVIC_EXTI12}
#define EXTI12PC12       (EXTI_Mapping_t){PIN_12, EXTI12, GPIOC, NVIC_EXTI12}
#define EXTI12PD12       (EXTI_Mapping_t){PIN_12, EXTI12, GPIOD, NVIC_EXTI12}

#define EXTI13PA13       (EXTI_Mapping_t){PIN_13, EXTI13, GPIOA, NVIC_EXTI13}
#define EXTI13PB13       (EXTI_Mapping_t){PIN_13, EXTI13, GPIOB, NVIC_EXTI13}
#define EXTI13PC13       (EXTI_Mapping_t){PIN_13, EXTI13, GPIOC, NVIC_EXTI13}
#define EXTI13PD13       (EXTI_Mapping_t){PIN_13, EXTI13, GPIOD, NVIC_EXTI13}

#define EXTI14PA14       (EXTI_Mapping_t){PIN_14, EXTI14, GPIOA, NVIC_EXTI14}
#define EXTI14PB14       (EXTI_Mapping_t){PIN_14, EXTI14, GPIOB, NVIC_EXTI14}
#define EXTI14PC14       (EXTI_Mapping_t){PIN_14, EXTI14, GPIOC, NVIC_EXTI14}
#define EXTI14PD14       (EXTI_Mapping_t){PIN_14, EXTI14, GPIOD, NVIC_EXTI14}

#define EXTI15PA15       (EXTI_Mapping_t){PIN_15, EXTI15, GPIOA, NVIC_EXTI15}
#define EXTI15PB15       (EXTI_Mapping_t){PIN_15, EXTI15, GPIOB, NVIC_EXTI15}
#define EXTI15PC15       (EXTI_Mapping_t){PIN_15, EXTI15, GPIOC, NVIC_EXTI15}
#define EXTI15PD15       (EXTI_Mapping_t){PIN_15, EXTI15, GPIOD, NVIC_EXTI15}


// @ref EXTI_Trigger_define
#define EXTI_Falling_edge		0
#define EXTI_Rising_edge 		1
#define EXTI_BOTH_edges 		2


// @ref EXTI_Enable_define
#define EXTI_IRQ_Enabled		1
#define EXTI_IRQ_Disabled		0

//GPIO PORT MASK

#define PA						0x00
#define PB						0x01
#define PC						0x02
#define PD						0x03
/*
* ===============================================
*      APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void EXTI_init(EXTI_PinConfig_t *pinConfig);
void EXTI_deInit(void);
void EXTI_Update(EXTI_PinConfig_t *pinConfig);


#endif /* INC_EXTI_H_ */
