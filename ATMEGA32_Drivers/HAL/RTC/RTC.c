/*
 * RTC.c
 *
 *  Created on: 7 Sept 2023
 *      Author: Alaa Wahba
 */

#include "RTC.h"

RTC_t G_rtc;
void RTC_init() {
	_delay_ms(500);
	I2C_init();
	I2C_Start();
	I2C_SendSlaveAddress(RTC_Address, 0);
	I2C_Write(CONTROL_REG);  //Address to control register
	I2C_Write(0x00);
	I2C_Stop();

}
void RTC_setTimeDate(RTC_t *rtc) {
	G_rtc = *rtc;

	if (G_rtc.mode == HOURS_12) {
		G_rtc.hour |= 0x40;
		G_rtc.hour |= G_rtc.AM_PM;
	}
	I2C_Start();

	I2C_SendSlaveAddress(RTC_Address, 0);
	I2C_Write(SECONDS_REG);  //Address to seconds register

	I2C_Write(G_rtc.second);
	I2C_Write(G_rtc.minute);
	I2C_Write(G_rtc.hour);
	I2C_Write(G_rtc.day);
	I2C_Write(G_rtc.date);
	I2C_Write(G_rtc.month);
	I2C_Write(G_rtc.year);

	I2C_Stop();
}

void RTC_getDateTime(RTC_t *rtc) {

	I2C_Start();
	I2C_SendSlaveAddress(RTC_Address, 0);
	I2C_Write(SECONDS_REG);
	I2C_Start();
	I2C_Write(RTC_Address + 1);
	rtc->second = I2C_Read(1);
	rtc->minute = I2C_Read(1);
	rtc->hour = I2C_Read(1);
	if (G_rtc.mode == HOURS_12) {
		// get the value of AM or PM
		rtc->AM_PM = GET(rtc->hour, 5);
		// the value of hour is only 5bit of HOURS REGISTER
		rtc->hour &= 0x1F;
	}
	rtc->day = I2C_Read(1);
	rtc->date = I2C_Read(1);
	rtc->month = I2C_Read(1);
	rtc->year = I2C_Read(0);

	I2C_Stop();

}

void RTC_getDateTimeStr(RTC_t *rtc, char *date, char *time) {
	char *day, *AM_PM = "";


	if (rtc->AM_PM == 0x20) {
		AM_PM = "PM";
	} else {
		AM_PM = "AM";
	}
	if (G_rtc.mode == HOURS_12)
		sprintf(time, "Time : %.2x:%.2x:%.2x %2s", rtc->hour, rtc->minute,
				rtc->second, AM_PM);
	else
		sprintf(time, "Time : %.2x:%.2x:%.2x ", rtc->hour, rtc->minute, rtc->second);

	switch (rtc->day) {
	case SAT:
		day = "SAT";
		break;
	case SUN:
		day = "SUN";
		break;
	case MON:
		day = "MON";
		break;
	case TUE:
		day = "TUE";
		break;
	case WED:
		day = "WED";
		break;
	case THU:
		day = "THU";
		break;
	case FRI:
		day = "FRI";
		break;

	}
	sprintf(date, "Date : %.2x/%.2x/%x %s", rtc->date, rtc->month, rtc->year, day);



}
