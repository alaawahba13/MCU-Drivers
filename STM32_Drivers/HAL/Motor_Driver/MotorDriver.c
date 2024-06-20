/*
 * MotorDriver.c
 *
 *  Created on: Apr 30, 2024
 *      Author: Alaa
 */

#include "MotorDriver.h"

void Motor_init(Motor_t *Motor_pinConfig) {
	TIM_ConfigType timConfig;
	GPIO_PinConfig_t GPIO_pinConfig;
	PWM_ConfigType pwmConfig;
//Configure IN1,IN2,EN as output
	GPIO_pinConfig.Pin_Number = Motor_pinConfig->IN1;
	GPIO_pinConfig.MODE = MODE_OUTPUT_PP;
	GPIO_pinConfig.Output_Speed = SPEED_10M;
	GPIO_init(Motor_pinConfig->IN1_port, &GPIO_pinConfig);
	GPIO_pinConfig.Pin_Number = Motor_pinConfig->IN2;
	GPIO_init(Motor_pinConfig->IN2_port, &GPIO_pinConfig);

	GPIO_pinConfig.Pin_Number = Motor_pinConfig->EN;
	GPIO_pinConfig.MODE = MODE_OUTPUT_AF_PP;
	GPIO_init(Motor_pinConfig->EN_port, &GPIO_pinConfig);
	// configure timer
	timConfig.AutoReloadValue = 625;
	timConfig.AutoReloadBuffer = Disable_ARR_Buffer;
	timConfig.Tim_Direction = Up_Counting;
	timConfig.ClockFactor = Div_1;
	timConfig.UDI_State = Disable_Interrupt;
	timConfig.AlignedMode = EdgeAligned_Mode;
	timConfig.Prescalar = 31;
	TIM_Init(Motor_pinConfig->TIM, &timConfig);
	//configure pwm
	pwmConfig.AutoReloadValue = 625;
	pwmConfig.Freq = 1;
	pwmConfig.Channel = Motor_pinConfig->TIM_Channel;
	pwmConfig.Mode = PWM_11;
	PWM_Init(Motor_pinConfig->TIM, &pwmConfig);
}
void Motor_Clockwise(Motor_t *Motor_pinConfig, uint16 speed) {
	GPIO_WritePin(Motor_pinConfig->IN1_port, Motor_pinConfig->IN1, PIN_HIGH);
	GPIO_WritePin(Motor_pinConfig->IN2_port, Motor_pinConfig->IN2, PIN_LOW);
	PWM_voidSetDutyCycle(Motor_pinConfig->TIM, Motor_pinConfig->TIM_Channel,
			speed);
}
void Motor_AntiClockwise(Motor_t *Motor_pinConfig, uint16 speed) {
	GPIO_WritePin(Motor_pinConfig->IN1_port, Motor_pinConfig->IN1, PIN_LOW);
	GPIO_WritePin(Motor_pinConfig->IN2_port, Motor_pinConfig->IN2, PIN_HIGH);
	PWM_voidSetDutyCycle(Motor_pinConfig->TIM, Motor_pinConfig->TIM_Channel,
			speed);
}
void Motor_Stop(Motor_t *Motor_pinConfig){
	GPIO_WritePin(Motor_pinConfig->IN1_port, Motor_pinConfig->IN1, PIN_LOW);
		GPIO_WritePin(Motor_pinConfig->IN2_port, Motor_pinConfig->IN2, PIN_LOW);
		PWM_voidSetDutyCycle(Motor_pinConfig->TIM, Motor_pinConfig->TIM_Channel,
				0);
}
