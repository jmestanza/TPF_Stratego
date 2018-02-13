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
void blitBitmap(ALLEGRO_BITMAP *dst,ALLEGRO_BITMAP* who,int x,int y) {
	ALLEGRO_BITMAP *old = al_get_target_bitmap();
	al_set_target_bitmap(dst);
	al_draw_bitmap(who,x,y,0);
	al_set_target_bitmap(old);
}

void blitTextCentered(Viewer* view,ALLEGRO_BITMAP *dst,string text,string font,string color) {
	ALLEGRO_BITMAP  *old = al_get_target_bitmap();
	ALLEGRO_FONT* fontAl = view->getFont(font);
	ALLEGRO_COLOR colorAl = view->getColor(color);

	int width = al_get_bitmap_width(dst);
	int height = al_get_bitmap_height(dst);

	int bbx,bby,bbw,bbh;
	al_get_text_dimensions(fontAl,text.c_str(),&bbx,&bby,&bbw,&bbh);

	int x = width / 2 - bbw / 2 - bbx;
	int y = height / 2 - bbh / 2 - bby;

	al_set_target_bitmap(dst);

	al_draw_text(fontAl,colorAl,x,y,0,text.c_str());

	al_set_target_bitmap(old);
}