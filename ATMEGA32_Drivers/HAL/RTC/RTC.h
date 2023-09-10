/*
 * RTC.h
 *
 *  Created on: 7 Sept 2023
 *      Author: Alaa Wahba
 */

#ifndef HAL_RTC_RTC_H_
#define HAL_RTC_RTC_H_

#include "../../Atmega32/inc/I2C.h"


#define RTC_Address 			(uint8)(0xD0)

// @ref Mode
#define HOURS_12				1
#define HOURS_24				0

// @ref AM_PM
#define HOURS_AM				(uint8)0x00
#define HOURS_PM				(uint8)0x20

// Registers addresses

#define CONTROL_REG 			0x07
#define SECONDS_REG				0x00

typedef enum Days{
	MON=0,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
}Days;

typedef struct rtc{
	uint8 hour;
	uint8 minute;
	uint8 second;
	uint8 date;
	uint8 month;
	uint8 year;
	uint8 mode; 	// @ref Mode
	uint8 AM_PM;	// @ref AM_PM
	Days day;

}RTC_t;

void RTC_init();
void RTC_getDateTime(RTC_t *rtc);
void RTC_setTimeDate(RTC_t *rtc);
void RTC_getDateTimeStr(RTC_t *rtc, char *date, char *time);

#endif /* HAL_RTC_RTC_H_ */
