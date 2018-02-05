#pragma once

#include <boost\asio\io_service.hpp>
#include <framework\controller\controller.h>
#include <framework\model\network\NetworkProtocol.h>
#include <framework\view\gui\gui.h>

using namespace boost::asio;

/*** Español: sysgame es el organo ejecutivo del juego. Todo lo que pasa en el juego en definitiva
lo comanda sygame a partir de sus atributos, la vista, el controlador, y el modelo.
***/

struct NETWORK_EVENT {
	string msg;
};

class NetContInt : public NetworkProtocol { //network-controller interface
	public:
		NetContInt(io_service *service, Sysgame *_sysgame);
		~NetContInt();
		void setController(Controller *controller);

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
		
		Sysgame(io_service*);
		void update(); // handle all neccesary updates
		void setNewController(Controller *newController);
		Controller *getController();

		~Sysgame();

	private:
		io_service *service;
		Controller * controller;
		UI *ui;
		NetworkProtocol *network;
};

