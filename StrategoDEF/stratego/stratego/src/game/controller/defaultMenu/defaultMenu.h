#pragma once

/*
NO SE USA: para borrar
*/
#include <framework\sysgame\sysgame.h>
#include <framework\controller\controller.h>

class defaultMenu : Controller{
	public:
		defaultMenu(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		~defaultMenu();
};

