#include "TextInput.h"

#include <string>
#include <framework\utils\random_number.h>
#include <iostream>

using namespace std;
TextInput::TextInput(Sysgame *sys, string name) : Widget(sys,name){
	code = to_string(randomNumber());
	_startDraw = 0;
}
void TextInput::configure(pair<float, float> _pos,bool centered) {
	pos = _pos;
	ALLEGRO_BITMAP *a = view->getImg("text_input");
	this->size = pair<float, float>(al_get_bitmap_width(a),al_get_bitmap_height(a));
	if (centered) {
		pos.first -= size.first / 2;
		pos.second -= size.second / 2;
	}
}
void TextInput::handleEvent(ALLEGRO_EVENT *ev) {

}
void TextInput::startDrawing() {
	if (_iconShown) {
		view->show("text_input_"+code, "text_input_" + code, this->pos.first, this->pos.second);
	}else {
		view->show("text_input", "text_input_" + code, this->pos.first, this->pos.second);
	}
}
void TextInput::addIcon(string img) {
	_iconShown = 1;
	ALLEGRO_BITMAP *a = view->getImg("text_input");
	ALLEGRO_BITMAP *icon = view->getImg(img);

	ALLEGRO_BITMAP *nuevo = al_create_bitmap(al_get_bitmap_width(a), al_get_bitmap_height(a));

	float a_height = al_get_bitmap_height(a);
	float icon_height = al_get_bitmap_height(icon);

	float dx = 10;
	float dy = a_height/2-icon_height /2;

	al_set_target_bitmap(nuevo);
	al_draw_bitmap(a,0,0,0);
	al_draw_bitmap(icon, dx, dy, 0);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	view->loadFromBitmap(nuevo, "text_input_" + code);
	//if (_startDraw) view->stopShow("text_input_" + code);
	//cout << "called\n";
	//view->show("text_input_" + code, "text_input_" + code,this->pos.first,this->pos.second);
	//view->show("")
}
void TextInput::stopDrawing(){
	view->stopShow("text_input_" + code);
}

TextInput::~TextInput(){
}
