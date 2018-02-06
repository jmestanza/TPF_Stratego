#include "sysgame.h"

NETWORK_EVENT::NETWORK_EVENT(string _msg) : msg(_msg){}

NetContInt::NetContInt(io_service *service) : NetworkProtocol(service) {
	
}
void NetContInt::onPackageRecv(string &pkgName, map<string, string> &content) {
	this->mySygame->getController()->onNetPack(pkgName, content);
}
void NetContInt::setSysgamePointer(Sysgame *_sysgame) {
	this->mySygame = _sysgame;
}
void NetContInt::onConnect() {
	NETWORK_EVENT *ev = new NETWORK_EVENT("connected");
	this->mySygame->getController()->onNetEvent(ev);
	delete ev;
}
void NetContInt::onConnFailed(string err) {
	NETWORK_EVENT *ev = new NETWORK_EVENT("connfailed");
	this->mySygame->getController()->onNetEvent(ev);
	delete ev;
}
void NetContInt::onLostConnection(string err) {
	NETWORK_EVENT *ev = new NETWORK_EVENT("connlost");
	this->mySygame->getController()->onNetEvent(ev);
	delete ev;
}
void NetContInt::onSent() {
	NETWORK_EVENT *ev = new NETWORK_EVENT("msgsent");
	this->mySygame->getController()->onNetEvent(ev);
	delete ev;
}

NetContInt::~NetContInt() {

}
Sysgame::Sysgame(string xmlScreenConfig) : network(&service){
	network.setSysgamePointer(this);
	controller = nullptr;
	ui = UI();
	view = Viewer();
	view.loadConfFile(xmlScreenConfig);
	view.start();
	
}

Controller *Sysgame::getController() {
	return controller;
}
UI *Sysgame::getUI() {
	return &ui;
}
Sysgame::~Sysgame() {
	delete controller;
}

void Sysgame::setNewController(Controller *_contr) {
	delete controller;
	controller = _contr;
}

void Sysgame::update() {

	ALLEGRO_EVENT ev;
	if (view.getNextEvent(&ev)) ui.HandleEvent(&ev);
	service.poll();
	
}
Viewer* Sysgame::getAllegroHandler() {
	return &view;
}
