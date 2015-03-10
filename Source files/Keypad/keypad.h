#ifndef KEYPAD_H_
#define KEYPAD_H_
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bit_handler.h"

#define KEYPAD_HEIGHT 4
#define KEYPAD_WIDTH  4
#define KEYPAD_STRING_SIZE KEYPAD_HEIGHT*KEYPAD_WIDTH

#ifndef KEYPAD_OUT_PORT
#define KEYPAD_OUT_PORT PORTB
#endif

#ifndef KEYPAD_IN_PORT
#define KEYPAD_IN_PORT PINB
#endif

#ifndef KEYPAD_DIR_PORT
#define KEYPAD_DIR_PORT DDRB
#endif

typedef struct{
	char * keys, * keys_old;
	int keys_pressed,amount_pressed;
}Keypad;

char KEY_MATRIX [KEYPAD_HEIGHT][KEYPAD_WIDTH] = {
												{'1','2','3','A'},
												{'4','5','6','B'},
												{'7','8','9','C'},
												{'*','0','#','D'}};

void init_keypad(Keypad * keypad){
	KEYPAD_DIR_PORT = BOT_NIBBLE_MASK;
	keypad->keys = malloc(sizeof(char)*KEYPAD_STRING_SIZE);
}

void clean_keypad(Keypad * keypad){
	if(keypad->keys!=NULL)
		free(keypad->keys);
	if(keypad->keys_old!=NULL)
		free(keypad->keys_old);
}

bool is_key_new(Keypad keypad){
	return strcmp(keypad.keys,keypad.keys_old);
}
int suc;
char * get_keypad(){
	// Return array of chars, instead of single chars
	uint8_t line, column, success = 0;
	char * keys_scanned = malloc(sizeof(char)*KEYPAD_STRING_SIZE);
	
	for(line=0;line<KEYPAD_HEIGHT;line++){
		port_set(KEYPAD_OUT_PORT,1<<line,BOT_NIBBLE_MASK);
		
		// Scan each column starting from top nibble and check if a key was pressed
		for(column=KEYPAD_HEIGHT;column<KEYPAD_HEIGHT+KEYPAD_WIDTH;column++)
			if(bit_get(KEYPAD_IN_PORT,column))
				keys_scanned[success++] = KEY_MATRIX[line-1][column];
	}
	suc = success;
	return keys_scanned;
}

void update_key(Keypad * keypad){
	memcpy(keypad->keys,keypad->keys_old,KEYPAD_STRING_SIZE);
	keypad->amount_pressed = strlen(keypad->keys);
	keypad->keys_pressed++;
}

void check_key(Keypad * keypad){
	keypad->keys_old = get_keypad();
}

bool validate_key(Keypad * keypad){
	bool valid;
	check_key(keypad);
	if((valid=is_key_new(*keypad)))
		update_key(keypad);
	free(keypad->keys_old);
	return valid;
}

#endif