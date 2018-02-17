#include "checkbox.h"


int Checkbox::getStatus() {
	return _status;
}
Checkbox::Checkbox(Sysgame *sys,string name) : Widget(sys,name) {
	_status = 0;
}
void Checkbox::configure(string _imgA,string _imgB,pair<int,int> pos,bool centered) {
	imgA = _imgA; imgB = _imgB;
	pair<int,int> _size( al_get_bitmap_width(view->getImg(imgA)) , al_get_bitmap_height(view->getImg(imgB)));
	setPosSize(pos,_size,centered);
}
void Checkbox::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mx = ev->mouse.x;
		my = ev->mouse.y;
	}
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (insideMe(mx,my)) {
			if (_status) {
				_status = 0;
				view->changeShowImg("checkbox_"+name,imgA);
				onTickFunction(mySysgame,0);
			} else {
				_status = 1;
				view->changeShowImg("checkbox_"+name,imgB);
				onTickFunction(mySysgame,1);
			}
		}
	}
}
void Checkbox::startDrawing() {
	view->show(imgA,"checkbox_"+name,this->pos.first,this->pos.second);
}
void Checkbox::stopDrawing() {
	view->stopShow("checkbox_"+name);
}
void Checkbox::onTick(void(*func)(Sysgame*,int)) {
	onTickFunction = func;
}
Checkbox::~Checkbox() {

}