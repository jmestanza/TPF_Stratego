#include "sysgame.h"


NetContInt::NetContInt(io_service *service, Sysgame *_sysgame) : NetworkProtocol(service) , mySygame(_sysgame)  {
	
}
void NetContInt::onPackageRecv(string &PkgName, map<string, string> &content) {
	
}
Sysgame::Sysgame(io_service *_service) : service(_service) {}

Controller *Sysgame::getController() {
	return controller;
}

Sysgame::~Sysgame() {}
