#pragma once

/*
Pagina 2 de los créditos del juego

*/
#include <framework\controller\controller.h>

class AboutWindow2 : Controller{
public:
	AboutWindow2(Sysgame* sys);
	void onCreate();
	void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
	void onNetEvent(NETWORK_EVENT *ev);
	~AboutWindow2();
};

