#pragma once

#include <framework\controller\controller.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\sysgame\sysgame.h>

class ConnectMenu : Controller{
	private:
		int _startedToConnect;
		TextButton *connectButton;
		TextInput *input;
		int waitTime;
	public:
		ConnectMenu(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		void startToConnect();
		int startedToConnect();
		void setConnectionFailed();
		void createConnectButton();
		void setNotConnecting();
		~ConnectMenu();
};

