#include "controller.h"

Controller::Controller(Sysgame *_sysgame) : mySysgame(_sysgame) {
	view = _sysgame->getAllegroHandler();
}