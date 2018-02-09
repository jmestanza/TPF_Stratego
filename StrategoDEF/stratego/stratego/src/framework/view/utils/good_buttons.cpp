#include "good_buttons.h"


imgGroup g_blue() {
	return imgGroup("button_blue_a","button_blue_b","button_grey");
}
imgGroup g_green() {
	return imgGroup("button_green_a","button_green_b","button_grey");
}
imgGroup g_connectButton() {
	return imgGroup("button_big_green_a_V2", "button_big_green_b_V2", "button_grey");
}



void generateButtons(Viewer *view) {
	ALLEGRO_BITMAP *original = view->getImg("button_big_green_a");
	int width = al_get_bitmap_width(original);
	int height = al_get_bitmap_height(original);
	ALLEGRO_BITMAP *modified = al_create_bitmap(width,height);
	al_set_target_bitmap(modified);
	al_draw_bitmap(original,0,0,0);

	ALLEGRO_BITMAP *icon = view->getImg("icon_networking");
	int heightIcon = al_get_bitmap_height(icon);

	int dx = 15;
	int dy = height / 2 - heightIcon / 2;
	al_draw_bitmap(icon,dx,dy,0);

	view->loadFromBitmap(modified,"button_big_green_a_V2");

	ALLEGRO_BITMAP *modified2 = al_create_bitmap(width,height);
	ALLEGRO_BITMAP *original2 = view->getImg("button_big_green_b");
	al_set_target_bitmap(modified2);
	al_draw_bitmap(original2,0,0,0);
	al_draw_bitmap(icon,dx,dy,0);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	view->loadFromBitmap(modified2,"button_big_green_b_V2");
}