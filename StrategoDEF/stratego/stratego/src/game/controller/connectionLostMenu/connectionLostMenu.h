#pragma once

/*
Este controller toma accion cuando se muestra el menu de conexion perdida
*/

#include <framework\controller\controller.h>

class connectionLostMenu : public Controller{

	public:
		connectionLostMenu(Sysgame *sys);
		~connectionLostMenu();
		void onCreate();
		void onNetPack(string &package,map<string,string> &data) ;  // Handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev) ;
};

