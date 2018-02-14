#include "MouseFollower.h"

#include <iostream>
using namespace std;


MouseFollower::MouseFollower(Sysgame *sys,string name) : Widget(sys,name) {
	myBitmap = "";
	inScreen = 0;
}
void MouseFollower::setImg(string _img) {
	myBitmap = _img;
}
void MouseFollower::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		this->setMouse(ev->mouse.x,ev->mouse.y);
		
		if (myBitmap != "") {
			if (!inScreen) {

				view->show(myBitmap,name,mx,my);
				inScreen = 1;
			}
			view->changeShowImgPos(name,mx,my,1);
		}
	} else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		//this->callStopDrawing();
		if (inScreen) {
			view->stopShow(name);
			inScreen = 0;
		}
		myBitmap = "";
		
	}
}
void MouseFollower::startDrawing() {
	
}
void MouseFollower::hide() {
	//this->callStopDrawing();
	//this->myBitmap = "";
}
void MouseFollower::stopDrawing() {
	if (inScreen) {
		view->stopShow(name);
	}
	inScreen = 0;
}
void MouseFollower::setMouse(int _mx,int _my) {
	mx = _mx;
	my = _my;
}

MouseFollower::~MouseFollower() {}
