#include "background.h"

#include <framework\utils\random_number.h>

Background::Background(Sysgame *sysgame,string name) : Widget(sysgame,name){
	code = to_string(randomNumber());
}
void Background::configure(ALLEGRO_COLOR _color,pair<float,float> pos,pair<float,float> size,bool _centered) {
	color = _color;
	
	ALLEGRO_BITMAP* surface = al_create_bitmap(size.first,size.second);
	al_set_target_bitmap(surface);
	al_draw_filled_rectangle(0,0,size.first,size.second,color);
	view->loadFromBitmap(surface,"background_"+code);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	centered = _centered;
	this->pos = pos;
	this->size = size;
}
void Background::handleEvent(ALLEGRO_EVENT *ev) {
	
}
void Background::startDrawing() {
	mySysgame->getAllegroHandler()->show("background_"+code,"background_"+code,0,0);
}
void Background::stopDrawing() {
	mySysgame->getAllegroHandler()->stopShow("background_" + code);
}
Background::~Background() {
	
}
