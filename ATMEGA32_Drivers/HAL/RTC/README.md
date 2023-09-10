# EEPROM Example with LCD


```C
int main(void) {
	RTC_t rtc_r ={ 0x23, 0x59, 0x58, 0x10, 0x09, 0x23, HOURS_24, HOURS_PM, SUN };
	RTC_init();
	lcd_init();
	lcd_Clear_Screen();
	RTC_setTimeDate(&rtc_r);
	RTC_t rtc;
	char date[50];
	char time[50];
 while (1) {
	RTC_getDateTime(&rtc);
	RTC_getDateTimeStr(&rtc,date, time);
	lcd_GOTO_XY(0, 0);
	lcd_send_String(time);
	lcd_GOTO_XY(1, 0);
	lcd_send_String(date);

	}

 return 0;
 }
```
### Output



##### 12 Hour mode



https://github.com/alaawahba13/MCU-Drivers/assets/101985923/9ee64d24-88da-4d6e-97f7-2f096136e56c



##### 24 Hour mode




https://github.com/alaawahba13/MCU-Drivers/assets/101985923/16ac0ca5-f16d-4a90-a2ec-94e9e5781be5





