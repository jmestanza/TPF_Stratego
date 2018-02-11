#include "Animation.h"

#include <framework\utils\random_number.h>

Animation::Animation(Sysgame *sys,string name) : Widget(sys,name) {
	myNameCode = "animation_"+to_string(randomNumber());
	_started = 0;
	_drawing = 0;
	_efDrawing = 0;
}
void Animation::configure(vector <string> _images,pair<float,float> _pos,int centered) {
	images = _images;
	pos = _pos;
	ALLEGRO_BITMAP *img = view->getImg(images[0]);
	size = pair<float,float>(al_get_bitmap_width(img),al_get_bitmap_height(img));
	if (centered) {
		pos.first -= size.first/2;
		pos.second -= size.second / 2;
	}
}
void Animation::startDrawing() {
	_started = 1;
	view->show(images[_efDrawing] , myNameCode ,this->pos.first,this->pos.second );
}
void Animation::updateDrawing(){
	if (!_started) {
		startDrawing();
	} else {
		view->changeShowImg(myNameCode,images[_efDrawing]);
	}
}
void Animation::stopDrawing() {
	view->stopShow(myNameCode);
}
void Animation::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_TIMER) {
		_drawing ++;
		_efDrawing = _drawing * 0.5;
		if (_efDrawing == images.size()) _drawing = 0, _efDrawing = 0;
		updateDrawing();
	}
}

Animation::~Animation() {}
