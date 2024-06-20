/*
 * Stepper.h
 *
 *  Created on: May 14, 2024
 *      Author: Alaa
 */

#ifndef STEPPER_MOTOR_STEPPER_H_
#define STEPPER_MOTOR_STEPPER_H_

#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/TIM/TIM.h"

#define stepsperrev 4096

typedef struct {
	uint16 IN1_PIN;
	GPIO_Registers_t *IN1_PORT;
	uint16 IN2_PIN;
	GPIO_Registers_t *IN2_PORT;
	uint16 IN3_PIN;
	GPIO_Registers_t *IN3_PORT;
	uint16 IN4_PIN;
	GPIO_Registers_t *IN4_PORT;
} stepper_t;

void stepper_init(stepper_t *stepper_pinConfig);
void stepper_set_rpm(int rpm,stepper_t *stepper_pinConfig);
void stepper_half_drive(int step,stepper_t *stepper_pinConfig);
void stepper_step_angle(float angle, int direction, int rpm,stepper_t *stepper_pinConfig);

#endif /* STEPPER_MOTOR_STEPPER_H_ */
