///*
// * Ultrasonic.c
// *
// *  Created on: Mar 26, 2024
// *      Author: Alaa
// */
//
#include "UltraSonic.h"
static volatile uint8 TimeOutFlag = 0;
static void ultrasonicCB_Fun(void) {
	TimeOutFlag = 1;
}
void ultraSonic_init(Ultrasonic_t *ultrasonic_pinConfig) {

	/*Configure GPIO pins */
	// Set pin directions to input floating
	GPIO_PinConfig_t GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin_Number = ultrasonic_pinConfig->echo_pin;
	GPIO_InitStruct.MODE = MODE_INPUT_FLO;
	GPIO_init(ultrasonic_pinConfig->echo_port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin_Number = ultrasonic_pinConfig->trig_pin;
	GPIO_InitStruct.MODE = MODE_OUTPUT_PP;
	GPIO_InitStruct.Output_Speed = SPEED_2M;
	GPIO_init(ultrasonic_pinConfig->trig_port, &GPIO_InitStruct);
	GPIO_WritePin(ultrasonic_pinConfig->trig_port,
			ultrasonic_pinConfig->trig_pin, PIN_LOW);

	STK_init();

}

float ultraSonic_readDistance(Ultrasonic_t *ultrasonic_pinConfig) {
	uint32 Value1 = 0;
	uint32 Value2 = 0;
	float Distance = 0;  // cm

	GPIO_WritePin(ultrasonic_pinConfig->trig_port,
			ultrasonic_pinConfig->trig_pin, PIN_HIGH);
	STK_delayUs(10);
	GPIO_WritePin(ultrasonic_pinConfig->trig_port,
			ultrasonic_pinConfig->trig_pin, PIN_LOW);
	TimeOutFlag = 0;
	STK_SetInterval(1000000, ultrasonicCB_Fun);
	// wait for the echo pin to go high
	while ((GPIO_ReadPin(ultrasonic_pinConfig->echo_port, ultrasonic_pinConfig->echo_pin) == 0) && (TimeOutFlag == 0))
		;
	Value1 = STK_getElapsedTime();
	// wait for the echo pin to go low
	while ((GPIO_ReadPin(ultrasonic_pinConfig->echo_port, ultrasonic_pinConfig->echo_pin) == 1) && (TimeOutFlag == 0))
		;
	Value2 = STK_getElapsedTime();
	STK_stopInterval();
	Distance = (Value2 - Value1) * 0.034 / 2;
	return Distance;
}

