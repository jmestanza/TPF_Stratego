#include <framework\utils\random_number.h>
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
Sysgame::Sysgame() : network(&service) {
	network.setSysgamePointer(this);
	controller = nullptr;
	_quit = 0;
	ui = new UI();
	view = new Viewer();
	try {
		view->loadConfFile("resource/game_config.xml");
	} catch (AllegroHandlerException &e) {
		cout << "warning: coudn't load config file \n";
		cout << "info:" << e.what() << '\n';
	}
	view->start();
	try {
		view->loadImgFile("resource/images.xml");
		view->loadFontFile("resource/fonts.xml");
		view->loadAudioFile("resource/audios.xml");
		view->loadColorsFile("resource/colors.xml");
	} catch (AllegroHandlerException &e) {
		cout << "could't load data files \n";
		cout << "info: " << e.what() << '\n';
	}
}
void Sysgame::Quit() {
	_quit = 1;
}
Controller *Sysgame::getController() {
	return controller;
}
UI *Sysgame::getUI() {
	return ui;
}
Sysgame::~Sysgame() {
	//cout << "finish \n";
	delete controller;
	delete ui;
	delete view;
}

void Sysgame::setNewController(Controller *_contr) {
	delete controller;
	ui->eraseAll();
	controller = _contr;
	controller->onCreate();
}

void Sysgame::update() {

	ALLEGRO_EVENT ev;
	if (view->getNextEvent(&ev)) {
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			_quit = 1;
		}
		ui->HandleEvent(&ev);
	}
	ui->refreshDead();
	view->draw();
	service.poll();
}
bool Sysgame::quit() {
	return _quit;
}
Viewer* Sysgame::getAllegroHandler() {
	return view;
}
