/*
 * MotorDriver.h
 *
 *  Created on: Apr 30, 2024
 *      Author: Alaa
 */

#ifndef MOTOR_DRIVER_MOTORDRIVER_H_
#define MOTOR_DRIVER_MOTORDRIVER_H_

#include "../../MCAL/TIM/TIM.h"
#include "../../MCAL/GPIO/GPIO.h"

typedef struct{
	uint16 IN1;
	GPIO_Registers_t *IN1_port;
	uint16 IN2;
	GPIO_Registers_t *IN2_port;
	uint16 EN;
	GPIO_Registers_t *EN_port;
	TIM_Registers_t *TIM;
	uint8 TIM_Channel;
}Motor_t;

void Motor_init(Motor_t *Motor_pinConfig);
void Motor_Clockwise(Motor_t *Motor_pinConfig,uint16 speed);
void Motor_AntiClockwise(Motor_t *Motor_pinConfig,uint16 speed);
void Motor_Stop(Motor_t *Motor_pinConfig);
#endif /* MOTOR_DRIVER_MOTORDRIVER_H_ */
