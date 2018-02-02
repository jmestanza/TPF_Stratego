#include "naiveButton.h"
#include "Viewer.h"
#include "allegro5\allegro.h"
using namespace std;

NaiveButton::NaiveButton(Viewer *_view, pair<float, float> _pos, int centered, string _img_a, string _img_b) : Widget(_view){
	img_a = _img_a, img_b = _img_b;
	myViewName = "button_" + to_string(id);
	view->show(img_a, myViewName,_pos.first, _pos.second);
	pos = _pos;
}

void NaiveButton::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		view->changeShowImg(myViewName, img_b);
	}else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
		view->changeShowImg(myViewName, img_a);
	}
}
NaiveButton::~NaiveButton() {
	view->destroy(myViewName);
}
