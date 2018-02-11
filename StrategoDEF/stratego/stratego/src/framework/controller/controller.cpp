#include "controller.h"

Controller::Controller(Sysgame *_sysgame) : mySysgame(_sysgame) {
	view = _sysgame->getAllegroHandler();
}
void Controller::addWidget(Widget *widget) {
	mySysgame->getUI()->AddWidget(widget);
}
void Controller::eraseWidget(string name) {
	mySysgame->getUI()->RemoveWidget(name);
}
Controller::~Controller() {

}