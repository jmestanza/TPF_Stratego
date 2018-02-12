#pragma once

#include <allegro5\allegro.h>
#include <string>

#include <boost\asio\io_service.hpp>
#include <framework\controller\controller.h>
#include <framework\model\network\NetworkProtocol.h>
#include <framework\view\gui\gui.h>
#include <framework\view\allegro_manager\allegro_manager.h>

using namespace boost::asio;
using namespace std;

/*** Español: sysgame es el organo ejecutivo del juego. Todo lo que pasa en el juego en definitiva
lo comanda sygame a partir de sus atributos, la vista, el controlador, y el modelo.
***/
class SysgameException : public exception {
	private:
		string err;
	public:
		SysgameException(string err);
		virtual const char *what() const throw();
};


class Sysgame;
class Controller;

struct NETWORK_EVENT {
	string msg;
	NETWORK_EVENT(string msg);
};

class NetContInt : public NetworkProtocol { //network-controller interface
	public:
		NetContInt(io_service *service);
		~NetContInt();
		//void setController(Controller *controller);
		void setSysgamePointer(Sysgame *_sysgame);

		void onPackageRecv(string &PkgName, map<string, string> &content);
		
		void onConnect();
		void onConnFailed(string err);
		void onSent();
		void onLostConnection(string err);

	private:
		Sysgame *mySygame;
};

class Sysgame {
	public:
		
		Sysgame();

		Viewer *getAllegroHandler();
		void update(); // handle all neccesary updates
		void setNewController(Controller *newController);
		void loadConfigurationData(string xmlFile);
		void Quit();

		UI *getUI();
	
		bool quit();

		map<string,string> &getConfigurationData();

		Controller *getController();
		NetContInt *getNetwork();
		~Sysgame();
	private:
		map<string,string> configurationData;
		io_service service;
		Controller *controller;
		Controller *nextController;
		UI *ui;
		Viewer *view;
		NetContInt network;
		bool _quit;

};

