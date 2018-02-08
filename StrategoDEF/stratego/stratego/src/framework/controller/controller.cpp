#include "controller.h"

Controller::Controller(Sysgame *_sysgame) : mySysgame(_sysgame) {
	view = _sysgame->getAllegroHandler();
}
void Controller::addWidget(Widget *widget) {
	mySysgame->getUI()->AddWidget(widget);
}
Controller::~Controller() {

}