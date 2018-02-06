#pragma once

#include <framework\sysgame\sysgame.h>
#include <framework\controller\controller.h>

class menuTest : Controller{
	public:
		menuTest(Sysgame *sys);
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);

		~menuTest();
};

