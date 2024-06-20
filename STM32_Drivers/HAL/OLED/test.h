/*
 * test.h
 *
 *  Created on: 17-Jun-2019
 *      Author: poe
 */

#ifndef TEST_H_
#define TEST_H_

#include "OLED.h"
#include "../../MCAL/Lib/STM32_F103x6.h"


void TestLines (uint8 color);

void TestRectangles (uint8 color);

void TestFilledRectangles (uint8 color);

void TestFilledCircles(uint8 radius, uint16 color);

void TestCircles(uint8 radius, uint16 color);

void TestTriangles(uint8 color);

#endif /* TEST_H_ */
