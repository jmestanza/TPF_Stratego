#include "copyBitmap.h"

ALLEGRO_BITMAP* copyBitmap(ALLEGRO_BITMAP *input) {
	int width = al_get_bitmap_width(input);
	int height = al_get_bitmap_height(input);

	ALLEGRO_BITMAP* nuevo = al_create_bitmap(width,height);
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(nuevo);
	al_draw_bitmap(input,0,0,0);
	al_set_target_bitmap(old);
	return nuevo;
}