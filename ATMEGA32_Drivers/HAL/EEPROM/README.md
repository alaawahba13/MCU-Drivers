# EEPROM Example with LCD


```C
int main(void) {
	uint16 address = 0x0100;
	uint8 data[50];
	uint8 arr[50] = "Hello My Name is Alaa Wahba :) 7/8/2001";
	int size = strlen(&arr);

	lcd_init();
	lcd_Clear_Screen();
	EEPROM_init();
	EEPROM_Write(&arr[0], address,16);
	_delay_ms(10);
	EEPROM_Write(&arr[16], address +16, 16);
	_delay_ms(10);
	EEPROM_Write(&arr[32], address +32, size-32);
	_delay_ms(10);
	EEPROM_Read(data, address,size);
	lcd_send_String(data);

	while (1) {
		

	}

	return 0;
}

```
### Output

