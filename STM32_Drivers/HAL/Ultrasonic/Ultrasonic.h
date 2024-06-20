///*
// * Ultrasonic.h
// *
// *  Created on: Mar 26, 2024
// *      Author: Alaa
// */
//
#ifndef ULTRASONIC_ULTRASONIC_H_
#define ULTRASONIC_ULTRASONIC_H_

#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../MCAL/RCC/RCC.h"

typedef struct {
	GPIO_Registers_t *echo_port;
	uint16 echo_pin;
	GPIO_Registers_t *trig_port;
	uint16 trig_pin;
} Ultrasonic_t;

void ultraSonic_init(Ultrasonic_t *ultrasonic_pinConfig);
float ultraSonic_readDistance(Ultrasonic_t *ultrasonic_pinConfig);
#endif /* ULTRASONIC_ULTRASONIC_H_ */
