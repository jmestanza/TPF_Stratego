#pragma once

#include <framework\controller\controller.h>

class connectionLostMenu : public Controller{

	public:
		connectionLostMenu(Sysgame *sys);
		~connectionLostMenu();
		void onCreate();
		void onNetPack(string &package,map<string,string> &data) ;  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev) ;
};

