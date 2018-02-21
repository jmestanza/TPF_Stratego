#include <framework\utils\random_number.h>
#include <framework\view\utils\getKey.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\utils\getXMLFile.h>

#include "sysgame.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
using namespace std;



SysgameException::SysgameException(string _err) : err("SysgameException: " + _err) {

}
const char * SysgameException::what() const throw() {
	//string ans =  + err;
	return err.c_str();
}

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
	nextController = nullptr;
	getKeyInit();
	network.setSysgamePointer(this);
	try {
		network.ParseProtocolXML("resource/protocol.xml");
	} catch (NetworkProtocolException &e) {
		cout << "couldn't load network protocol: " << e.what() << '\n';
		throw SysgameException("Fatal sysgame exception! ");
	}
	controller = nullptr;
	_quit = 0;
	ui = new UI();
	view = new Viewer();
	try {
		loadConfigurationData("resource/game_config.xml");
	} catch (SysgameException &e) {
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
	} catch (XMLException &e) {
		cout << "could't load data files (XMLException)";
		cout << "info: " << e.what() << '\n';
	}
	generateButtons(view);
}
map<string,string>& Sysgame::getConfigurationData() {
	return configurationData;
}
void Sysgame::loadConfigurationData(string xmlFile) {
	int viewerScreenWidth,viewerScreenHeight;
	using boost::property_tree::ptree;
	ptree pt;
	getXMLFile(pt,xmlFile);
	if (pt.count("config") != 1) throw AllegroHandlerException("wrong xml file (config tag invalid)");
	ptree content = pt.get_child("config");

	if (content.count("screen_size") > 1) throw SysgameException("wrong xml file (screen tag is invalid)");
	if (content.count("screen_size") == 1) {
		ptree screen_sz = content.get_child("screen_size").get_child("<xmlattr>");
		if (screen_sz.count("width") != 1) {
			throw SysgameException("wrong xml file (screen size invalid)");
		}
		if (screen_sz.count("height") != 1) {
			throw SysgameException("wrong xml file (screen size invalid)");
		}
		string screen_width = screen_sz.get<string>("width");
		string screen_height = screen_sz.get<string>("height");
		try {
			viewerScreenWidth = stoi(screen_width);
			viewerScreenHeight = stoi(screen_height);
		} catch (invalid_argument &e) {
			viewerScreenWidth = 800;
			viewerScreenHeight = 600;
			throw SysgameException("wrong xml file (screen size values invalid)");
		}
	}
	if (content.count("port") > 1) {
		throw SysgameException("wrong xml file 'network_port' tag is invalid");
	} else if (content.count("port") == 1) {
		ptree network_port = content.get_child("port").get_child("<xmlattr>");
		if (network_port.count("value") != 1) {
			throw SysgameException("invalid network port tag (no attr 'value')");
		}
		configurationData["port"] = network_port.get<string>("value");
		try {
			stoi(configurationData["port"]);
		} catch (invalid_argument &e) {
			configurationData["port"] = "9999";
			throw SysgameException("configuration data 'port' is invalid (couldn't convert to integer)");
		}
	} else {
		configurationData["port"] = "9999";
		throw SysgameException("error: invalid network port (setting default)");
	}


	if (content.count("debug") >= 1) view->setDebugFlag();

	view->setScreenSize(pair<float,float>(viewerScreenWidth,viewerScreenHeight));
}
void Sysgame::Quit() {
	_quit = 1;
}
bool Sysgame::isValidPos(pair<int,int> pos) {
	if ((0 <= pos.first) && (pos.first <= 9)) {
		if ((0 <= pos.second) && (pos.second <= 9)) {
			return true;
		}
	}
	return false;
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
	nextController = _contr;
}

void Sysgame::update() {

	ALLEGRO_EVENT ev;
	while (view->getNextEvent(&ev)) {
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			_quit = 1;
		}
		ui->HandleEvent(&ev);
	}
	try {
		ui->refreshDead();
		view->draw();
	} catch (AllegroHandlerException &e) {
		cerr << e.what() << '\n';
	} 
	
	service.poll();

	if (nextController != nullptr) {
		ui->eraseAll();
		ui->refreshDead();
		delete controller;
		controller = nextController;
		controller->onCreate();

		nextController = nullptr;
	}
}
bool Sysgame::quit() {
	return _quit;
}
Viewer* Sysgame::getAllegroHandler() {
	return view;
}
NetContInt *Sysgame::getNetwork() {
	return &network;
}