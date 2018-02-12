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

	allegroCodes[ALLEGRO_KEY_A] = 'a';
	allegroCodes[ALLEGRO_KEY_B] = 'b';
	allegroCodes[ALLEGRO_KEY_C] = 'c';
	allegroCodes[ALLEGRO_KEY_D] = 'd';
	allegroCodes[ALLEGRO_KEY_E] = 'e';
	allegroCodes[ALLEGRO_KEY_F] = 'f';
	allegroCodes[ALLEGRO_KEY_G] = 'g';
	allegroCodes[ALLEGRO_KEY_H] = 'h';
	allegroCodes[ALLEGRO_KEY_I] = 'i';
	allegroCodes[ALLEGRO_KEY_J] = 'j';
	allegroCodes[ALLEGRO_KEY_K] = 'k';
	allegroCodes[ALLEGRO_KEY_L] = 'l';
	allegroCodes[ALLEGRO_KEY_M] = 'm';
	allegroCodes[ALLEGRO_KEY_N] = 'n';
	allegroCodes[ALLEGRO_KEY_O] = 'o';
	allegroCodes[ALLEGRO_KEY_P] = 'p';
	allegroCodes[ALLEGRO_KEY_Q] = 'q';
	allegroCodes[ALLEGRO_KEY_R] = 'r';
	allegroCodes[ALLEGRO_KEY_S] = 's';
	allegroCodes[ALLEGRO_KEY_T] = 't';
	allegroCodes[ALLEGRO_KEY_U] = 'u';
	allegroCodes[ALLEGRO_KEY_V] = 'v';
	allegroCodes[ALLEGRO_KEY_W] = 'w';
	allegroCodes[ALLEGRO_KEY_X] = 'x';
	allegroCodes[ALLEGRO_KEY_Y] = 'y';
	allegroCodes[ALLEGRO_KEY_Z] = 'z';
}

char getKey(int code) {
	if (allegroCodes.find(code) == allegroCodes.end()) return -1;
	return allegroCodes[code];
}