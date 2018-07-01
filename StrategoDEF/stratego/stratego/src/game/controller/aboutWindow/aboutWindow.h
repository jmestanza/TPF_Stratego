#pragma once

/*
Este controller se muestra cuando se quieren ver los creditos del juego
*/

#include <framework\controller\controller.h>

class AboutWindow : Controller{
	public:
		AboutWindow(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data);  // Handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		~AboutWindow();
};

