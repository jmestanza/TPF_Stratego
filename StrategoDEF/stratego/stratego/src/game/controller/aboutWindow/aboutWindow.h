#pragma once

#include <framework\controller\controller.h>

class AboutWindow : Controller{
	public:
		AboutWindow(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		~AboutWindow();
};

