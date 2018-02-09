#include "TextInput.h"

#include <string>
#include <framework\utils\random_number.h>
#include <framework\view\utils\getKey.h>
#include <framework\view\utils\copyBitmap.h>
#include <iostream>

using namespace std;
TextInput::TextInput(Sysgame *sys, string name) : Widget(sys,name){
	code = to_string(randomNumber());
	_startDraw = 0;
	startPointX = 10;
	shownText = "";
	smallFont = "roboto_small";
	myDefaultFont = "roboto_v1";
	_smallTextAdded = 0;
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
void TextInput::handleEvent(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev->keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			if (shownText.size() > 0) {
				shownText.pop_back();
				updateDrawing();
			}
		} else {
			char k = getKey(ev->keyboard.keycode);
			if (k != -1) {
				shownText.push_back(getKey(ev->keyboard.keycode));
				updateDrawing();
			}
		}
	} else if (ev->type == ALLEGRO_EVENT_TIMER) {
		/// called 10 times per second
		/// we check time and update tile
		auxCount ++;

		int lastShowTile = _showTile;
		_showTile = auxCount < 5;
		auxCount = auxCount >= 10 ? 0 : auxCount;
		if (_showTile != lastShowTile) updateDrawing();
	}
}
void TextInput::updateDrawing() {
	ALLEGRO_BITMAP *myBitmap;
	ALLEGRO_BITMAP *base;
	ALLEGRO_FONT *myFont;
	
	myBitmap = view->getImg("text_input_" + code);
	base = view->getImg("text_input_base_" + code);
	myFont = view->getFont(myDefaultFont);
	

	al_set_target_bitmap(myBitmap);

	int height = al_get_bitmap_height(myBitmap);
	
	int bbx,bby,bbw,bbh;

	al_get_text_dimensions(myFont,
		shownText.c_str(),
		&bbx,&bby,&bbw,&bbh);
	int py = (height / 2 - (bby + bbh) / 2) - 3;

	al_draw_bitmap(base,0,0,0);
	al_draw_text(view->getFont(myDefaultFont),
		al_map_rgb(0,0,0),startPointX,py,ALLEGRO_ALIGN_LEFT,
		shownText.c_str());
	if (_showTile) {
		int lastX = startPointX + bbx + bbw + 5;
		al_draw_line(lastX,5,lastX,height-5,al_map_rgb(0,0,0),1);
	}
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
	//cout << "text:"<<shownText << '\n';

}
void TextInput::startDrawing() {
	view->show("text_input_"+code, "text_input_" + code, this->pos.first, this->pos.second);
	if (_smallTextAdded) view->show(smallTextName,smallTextName,smallTextX,smallTextY);
	
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

	view->loadFromBitmap(copyBitmap(nuevo), "text_input_base_" + code);
	view->loadFromBitmap(nuevo,"text_input_" + code);

	startPointX += dx + al_get_bitmap_width(icon);

	//if (_startDraw) view->stopShow("text_input_" + code);
	//cout << "called\n";
	//view->show("text_input_" + code, "text_input_" + code,this->pos.first,this->pos.second);
	//view->show("")
}
void TextInput::addSmallText(string msg) {
	if (_smallTextAdded) return; // nothing to do!

	ALLEGRO_FONT *myFont = view->getFont(smallFont);

	int width = al_get_text_width(myFont,msg.c_str());
	int height = 20;
	ALLEGRO_BITMAP* text_area = al_create_bitmap(width,height);
	

	al_set_target_bitmap(text_area);

	al_draw_text(myFont,
		al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,
		msg.c_str());
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));


	smallTextName = "text_input_small_text_" + code;
	view->loadFromBitmap(text_area,smallTextName);
	
	smallTextX = this->pos.first + this->size.first - width - 10;
	smallTextY = this->pos.second - height;

	_smallTextAdded = 1;
}
void TextInput::stopDrawing(){
	view->stopShow("text_input_" + code);
	if (_smallTextAdded) {
		view->stopShow(smallTextName);
		view->eraseLoaded(smallTextName);
	}
}

TextInput::~TextInput(){
}
