#pragma once

#include <framework\controller\controller.h>
#include <framework\sysgame\sysgame.h>

class ConnectMenu : Controller{
	public:
		ConnectMenu(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		~ConnectMenu();
};

