#include "background.h"

#include <framework\utils\random_number.h>

Background::Background(Sysgame *sysgame,string name) : Widget(sysgame,name){
	code = to_string(randomNumber());
	myImg = "background_" + code;
}
void Background::configure(string _color,pair<float,float> pos,pair<float,float> size,bool _centered) {
	color = view->getColor(_color);
	//cout << color.r << ' ' << color.g << ' ' << color.b << '\n';
	ALLEGRO_BITMAP* surface = al_create_bitmap(size.first,size.second);
	al_set_target_bitmap(surface);
	al_draw_filled_rectangle(0,0,size.first,size.second,color);
	view->loadFromBitmap(surface,"background_"+code);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	centered = _centered;
	this->pos = pos;
	this->size = size;
	loadImg = myImg;
}
void Background::configureImg(string img,pair<float,float> _pos,bool _centered) {
	ALLEGRO_BITMAP *surface = view->getImg(img);
	
	this->size = pair<float,float>(al_get_bitmap_width(surface),al_get_bitmap_height(surface));
	loadImg = img;

	this->pos = _pos;
	this->size = size;
	centered = _centered;
	if (centered) {
		this->pos.first -= this->size.first/2;
		this->pos.second -= this->size.second/2;
	}
}
void Background::handleEvent(ALLEGRO_EVENT *ev) {
	
}
void Background::startDrawing() {
	mySysgame->getAllegroHandler()->show(loadImg,myImg,this->pos.first,this->pos.second);
}
void Background::stopDrawing() {
	mySysgame->getAllegroHandler()->stopShow(myImg);
}
Background::~Background() {
	
}
