#include <framework\view\allegro_manager\allegro_manager.h>
#include "naive_button.h"
#include "allegro5\allegro.h"
#include <iostream>

using namespace std;

NaiveButton::NaiveButton(Sysgame *sys, string name) : Widget(sys,name){
}

void NaiveButton::start(pair<float, float> _pos, int centered, string _img_a, string _img_b,string _img_c){
	img_a = _img_a, img_b = _img_b ,_img_c = img_c;
	myViewName = "button_" + name;
	ALLEGRO_BITMAP* myBitMap = view->getImg(img_a);
	this->size = pair<float,float>( al_get_bitmap_width(myBitMap) , al_get_bitmap_height(myBitMap) );
	if (centered) {
		pos.first -= this->size.first/2;
		pos.second -= this->size.second/2;
	}
	pos = _pos;
}
void NaiveButton::startDrawing() {
	view->show(img_a,myViewName,pos.first,pos.second);
}
void NaiveButton::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (mx >= this->pos.first && mx <= this->pos.first + this->size.first) {
			if (my >= this->pos.second && my <= this->pos.second + this->size.second) {
				view->changeShowImg(myViewName,img_b);
			}
		}
	}else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
		view->changeShowImg(myViewName, img_a);
		onClickFunction(this->mySysgame);
	} else if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mx = ev->mouse.x;
		my = ev->mouse.y;
	}
}
void NaiveButton::onClick(void(*func)(Sysgame *)) {
	onClickFunction = func;
}
NaiveButton::~NaiveButton() {
	view->stopShow(myViewName);
}
