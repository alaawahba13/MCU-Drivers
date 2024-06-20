/*
 * Stepper.c
 *
 *  Created on: May 14, 2024
 *      Author: Alaa
 */

#include "Stepper.h"

void stepper_init(stepper_t *stepper_pinConfig) {
	RCC_init(RCC_PLL, 0, PLL_HSE, PLL_MUL_7);
//	RCC_setAPB1Prescalar(APB_DIV_2);
	TIM_ConfigType timConfig;
	timConfig.AutoReloadValue = 0xffff - 1;
	timConfig.AutoReloadBuffer = Disable_ARR_Buffer;
	timConfig.Tim_Direction = Up_Counting;
	timConfig.ClockFactor = Div_1;
	timConfig.UDI_State = Disable_Interrupt;
	timConfig.AlignedMode = EdgeAligned_Mode;
	timConfig.Prescalar = 71;
	TIM_Init(TIM1, &timConfig);
	GPIO_PinConfig_t GPIO_pinConfig;
	GPIO_pinConfig.Pin_Number = stepper_pinConfig->IN1_PIN;
	GPIO_pinConfig.MODE = MODE_OUTPUT_PP;
	GPIO_pinConfig.Output_Speed = SPEED_2M;
	GPIO_init(stepper_pinConfig->IN1_PORT, &GPIO_pinConfig);
	GPIO_pinConfig.Pin_Number = stepper_pinConfig->IN2_PIN;
	GPIO_init(stepper_pinConfig->IN2_PORT, &GPIO_pinConfig);
	GPIO_pinConfig.Pin_Number = stepper_pinConfig->IN3_PIN;
	GPIO_init(stepper_pinConfig->IN3_PORT, &GPIO_pinConfig);
	GPIO_pinConfig.Pin_Number = stepper_pinConfig->IN4_PIN;
	GPIO_init(stepper_pinConfig->IN4_PORT, &GPIO_pinConfig);
}
void stepper_set_rpm(int rpm, stepper_t *stepper_pinConfig) // Set rpm--> max 13, min 1,,,  went to 14 rev/min
{
	TIM_Delay_us(TIM1, 60000000 / stepsperrev / rpm);
}

void stepper_half_drive(int step, stepper_t *stepper_pinConfig) {
	switch (step) {
	case 0:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_HIGH);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_LOW);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_LOW);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_LOW);   // IN4
		break;

	case 1:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_HIGH);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_HIGH);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_LOW);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_LOW);   // IN4
		break;

	case 2:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_LOW);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_HIGH);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_LOW);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_LOW);   // IN4
		break;

	case 3:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_LOW);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_HIGH);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_HIGH);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_LOW);   // IN4
		break;

	case 4:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_LOW);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_LOW);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_HIGH);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_LOW);   // IN4
		break;

	case 5:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_LOW);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_LOW);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_HIGH);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_HIGH);   // IN4
		break;

	case 6:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_LOW);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_LOW);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_LOW);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_HIGH);   // IN4
		break;

	case 7:
		GPIO_WritePin(stepper_pinConfig->IN1_PORT, stepper_pinConfig->IN1_PIN, PIN_HIGH);   // IN1
		GPIO_WritePin(stepper_pinConfig->IN2_PORT, stepper_pinConfig->IN2_PIN, PIN_LOW);   // IN2
		GPIO_WritePin(stepper_pinConfig->IN3_PORT, stepper_pinConfig->IN3_PIN, PIN_LOW);   // IN3
		GPIO_WritePin(stepper_pinConfig->IN4_PORT, stepper_pinConfig->IN4_PIN, PIN_HIGH);   // IN4
		break;

	}
}

void stepper_step_angle(float angle, int direction, int rpm,
		stepper_t *stepper_pinConfig) {
	float anglepersequence = 0.703125;  // 360 = 512 sequences
	int numberofsequences = (int) (angle / anglepersequence);

	for (int seq = 0; seq < numberofsequences; seq++) {
		if (direction == 0)  // for clockwise
				{
			for (int step = 7; step >= 0; step--) {
				stepper_half_drive(step,stepper_pinConfig);
				stepper_set_rpm(rpm,stepper_pinConfig);
			}

		}

		else if (direction == 1)  // for anti-clockwise
				{
			for (int step = 0; step < 8; step++) {
				stepper_half_drive(step,stepper_pinConfig);
				stepper_set_rpm(rpm,stepper_pinConfig);
			}
		}
	}
}
