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

/*** Este archivo contiene:
- NetContInt: es una clase que contiene todos los metodos y callbacks del NetworkProtocol, pero ademas
esta preparada para poder trabajar en conjunto con el Controller del juego (La entidad que administra
la interfaz grafica, y decide que hacer ante los eventos que los distintos objetos de la interfaz grafica
llaman)

- NETWORK_EVENT: Esta clase sirve para estructurar un evento network, que es un tipo de evento
necesario para informarle al controller que algo sucedio con respecto al network (conexion perdida,
conexion establecida, etc). No se usa network event para la llegada de packetes.
Se usa un map que permite mayor libertad para estructurar la informacion de los paquetes.


- Sysgame: Es la clase principal que corre el juego. Todas las entidades del juego tienen
alguna entidad en el sysgame.

Por ejemplo el AllegroHandler (Llamado view), el NetContInt que es la clase que administra el network,
El controller, que es el controlador actual de un momento preciso del juego, la UI
que es la encargada de controlar los widgets, es decir todos los objetos graficos del juego, 

El loop principal del juego corre en sysgame.

**/
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
		void setSysgamePointer(Sysgame *_sysgame);

		void onPackageRecv(string &PkgName, map<string, string> &content); // callback de paquete recibido
		
		void onConnect();
		void onConnFailed(string err); // si falla la conexion (no se pudo establecer)
		void onSent(); // cuando se pudo enviar un mensaje se llama este callback
		void onLostConnection(string err); // si se perdio la conexion (ya se habia establecido)

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
		bool isValidPos(pair<int,int> pos);

		UI *getUI();
	
		bool quit();

		map<string,string> &getConfigurationData();

		Controller *getController();
		NetContInt *getNetwork();
		~Sysgame();
	private:
		map<string,string> configurationData; // la configuracion cargada del archivo xml
		io_service service;
		Controller *controller;
		Controller *nextController;
		UI *ui;
		Viewer *view; // El view, es la clase que administra la interfaz grafica de alllegro
		NetContInt network;
		bool _quit;

};

