#include <framework\view\allegro_manager\allegro_manager.h>
#include <framework\view\utils\copyBitmap.h>
#include <framework\utils\random_number.h>
#include "naive_button.h"
#include "allegro5\allegro.h"
#include <iostream>

using namespace std;

NaiveButton::NaiveButton(Sysgame *sys, string name) : Widget(sys,name){
	onClickFunction = nullptr;
	_iconMode = 0;
	_enabled = 1;
	myViewName = "button_" + to_string(randomNumber());
}

void NaiveButton::start(pair<float, float> _pos, int centered, string _img_a, string _img_b,string _img_c){
	img_a = _img_a, img_b = _img_b ,img_c = _img_c;
	
	ALLEGRO_BITMAP* myBitMap = view->getImg(img_a);
	this->size = pair<float,float>( al_get_bitmap_width(myBitMap) , al_get_bitmap_height(myBitMap) );
	pos = _pos;
	if (centered) {
		pos.first -= this->size.first/2;
		pos.second -= this->size.second/2;
	}
}
int NaiveButton::enabled() {
	return _enabled;
}
void NaiveButton::enable() {
	_enabled = 1;
	view->changeShowImg(myViewName,img_a);
}
void NaiveButton::disable() {
	_enabled = 0;
	view->changeShowImg(myViewName,img_c);
}
void NaiveButton::startDrawing() {
	view->show(img_a,myViewName,pos.first,pos.second);
}
void NaiveButton::handleEvent(ALLEGRO_EVENT *ev) {
	if (_enabled) {
		if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (mx >= this->pos.first && mx <= this->pos.first + this->size.first) {
				if (my >= this->pos.second && my <= this->pos.second + this->size.second) {
					view->changeShowImg(myViewName,img_b);
					_clicked = 1;
					onHardClickToOverride();
				}
			}
		} else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			view->changeShowImg(myViewName,img_a);
			if (_clicked) {
				if (onClickFunction) onClickFunction(this->mySysgame);
				onClickToOverride();
				onReleaseToOverride();
				_clicked = 0;
			}
		} else if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
			mx = ev->mouse.x;
			my = ev->mouse.y;
		}
	}
}
void NaiveButton::onClickToOverride() {
	//cout << "hi!\n";
}
void NaiveButton::onReleaseToOverride() {

}
void NaiveButton::onHardClickToOverride() {

}
void NaiveButton::addIcon(string img) {
	if (_iconMode) return;
	_iconMode = 1;
	//cout << "name = " << name << '\n';
	//cout << img_a << ' ' << img_b << ' ' << img_c << '\n';
	//// generate special bitmaps with additional icon
	ALLEGRO_BITMAP *newA = al_create_bitmap(this->size.first,this->size.second);
	ALLEGRO_BITMAP *newB = al_create_bitmap(this->size.first,this->size.second);
	ALLEGRO_BITMAP *newC = al_create_bitmap(this->size.first,this->size.second);

	ALLEGRO_BITMAP *icon = view->getImg(img);
	ALLEGRO_BITMAP *a = view->getImg(img_a);
	ALLEGRO_BITMAP *b = view->getImg(img_b);
	ALLEGRO_BITMAP *c = view->getImg(img_c);

	int icon_height = al_get_bitmap_height(icon);

	blitBitmap(newA,a,0,0);
	blitBitmap(newA,icon,15,this->size.second/2-icon_height/2);
	
	blitBitmap(newB,b,0,0);
	blitBitmap(newB,icon,15,this->size.second/2-icon_height/2);

	blitBitmap(newC,c,0,0);
	blitBitmap(newC,icon,15,this->size.second/2-icon_height/2);

	view->loadFromBitmap(newA,myViewName+"_a");
	view->loadFromBitmap(newB,myViewName+"_b");
	view->loadFromBitmap(newC,myViewName+"_c");

	img_a = myViewName + "_a";
	img_b = myViewName + "_b";
	img_c = myViewName + "_c";
}
void NaiveButton::onClick(void(*func)(Sysgame *)) {
	onClickFunction = func;
}

void NaiveButton::stopDrawing() {
	view->stopShow(myViewName);
}
NaiveButton::~NaiveButton() {
	if (_iconMode) {
		view->eraseLoaded(myViewName+"_a");
		view->eraseLoaded(myViewName+"_b");
		view->eraseLoaded(myViewName+"_c");
	}
}
