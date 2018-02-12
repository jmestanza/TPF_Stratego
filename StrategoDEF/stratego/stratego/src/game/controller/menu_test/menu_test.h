#pragma once

#include <framework\sysgame\sysgame.h>
#include <framework\controller\controller.h>
#include <framework\view\widgets\background.h>
#include <framework\view\widgets\Table.h>
#include <framework\view\widgets\TableButton.h>



class MenuTest : public Controller{
	public:
		int value;
		MenuTest(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);

		~MenuTest();
};

