#pragma once

/*
Controller para hacer pruebas
*/
#include <framework\controller\controller.h>

class showTimeTest : public Controller{
	private:
		string selectedItem;
		bool inScreen;
	public:
		
		string getSelectedItem();
		void setSelectedItem(string value);

		showTimeTest(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);

		~showTimeTest();
};

