#include "music_button.h"



music_button::music_button(Sysgame* sys,pair<float,float>_pos,string name,string _img_name) : Widget(sys,name) {
	myviewname = name;
	pos=_pos;
	image_name=_img_name;
	mySys=sys;
}


void music_button::handleEvent(ALLEGRO_EVENT * ev) {}

void music_button::stopDrawing() {
	view->stopShow(myviewname);
}

void music_button::startDrawing() {
	view->show(image_name,myviewname,this->pos.first,this->pos.second);
}

void music_button::onClick(void(*func)(Sysgame *)) {
		onClickFunction = func;
}

bool music_button::insideIconRange(int x,int y) {
	return ((x >= (pos.first - 40)) && (x <= (pos.first + 40)) && (y >= (pos.second - 50)) && (y <= (pos.second )));
}


music_button::~music_button() {}
