#include "getKey.h"

map<int,int> allegroCodes;

void getKeyInit() {
	allegroCodes[ALLEGRO_KEY_0] = '0';
	allegroCodes[ALLEGRO_KEY_1] = '1';
	allegroCodes[ALLEGRO_KEY_2] = '2';
	allegroCodes[ALLEGRO_KEY_3] = '3';
	allegroCodes[ALLEGRO_KEY_4] = '4';
	allegroCodes[ALLEGRO_KEY_5] = '5';
	allegroCodes[ALLEGRO_KEY_6] = '6';
	allegroCodes[ALLEGRO_KEY_7] = '7';
	allegroCodes[ALLEGRO_KEY_8] = '8';
	allegroCodes[ALLEGRO_KEY_9] = '9';
	allegroCodes[ALLEGRO_KEY_FULLSTOP] = '.';

	allegroCodes[ALLEGRO_KEY_PAD_0] = '0';
	allegroCodes[ALLEGRO_KEY_PAD_1] = '1';
	allegroCodes[ALLEGRO_KEY_PAD_2] = '2';
	allegroCodes[ALLEGRO_KEY_PAD_3] = '3';
	allegroCodes[ALLEGRO_KEY_PAD_4] = '4';
	allegroCodes[ALLEGRO_KEY_PAD_5] = '5';
	allegroCodes[ALLEGRO_KEY_PAD_6] = '6';
	allegroCodes[ALLEGRO_KEY_PAD_7] = '7';
	allegroCodes[ALLEGRO_KEY_PAD_8] = '8';
	allegroCodes[ALLEGRO_KEY_PAD_9] = '9';
}

char getKey(int code) {
	if (allegroCodes.find(code) == allegroCodes.end()) return -1;
	return allegroCodes[code];
}