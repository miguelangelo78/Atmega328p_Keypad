#include <avr/io.h>
#include "LCD_16x2/lcd.h"
#include "Keypad/keypad.h"

Keypad keypad;

void init(){
	init_keypad(&keypad);
	LCD_Init();
}

void display_str(char * str){
	LCD_Clear();
	LCD_Ws(str);
}

int main(void) {
	init();
	
	// Simply display the buttons being pressed:
	while(1)
		if(validate_key(&keypad))
			display_str(keypad.keys);
	
	clean_keypad(&keypad);
}