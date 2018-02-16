#pragma once

#include <framework\controller\controller.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\Animation.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\sysgame\sysgame.h>

class ConnectMenu : Controller{
	private:
		int _startedToConnect;
		TextButton *connectButton;
		TextInput *input;
		int waitTime;

		vector <string> connectContent;

		string status;
		string connectIP;

		string myName, opponentName;
		int gotName, gotOpponentName;

		int nameInputFilled;

		pair<float,float> infoPositionA; /// info message and icon places
		pair<float,float> infoPositionB;
		Widget* infoObjectA;
		Widget* infoObjectB;
		string mode;

		int localStart;		
	public:
		ConnectMenu(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		void startToConnect();
		int startedToConnect();
		void setConnectionFailed();
		void createConnectButton();
		void generateNameInput();
		void setNotConnecting();
		void setConnectionWaitTimeout();
		void setConnectionSuccess();
		void eraseConnectContent();
		void setInfoObjects(Widget* A,Widget* B);
		void eraseInfoObjects();
		void waitForConnection();
		void goToGame();
		Animation* generateAnimationWidget(string name);
		screenText* generateScreenText(string msg,string font,string name);
		string getConnectIP();
		vector<string> &getConnectContent();
		void setStatus(string status);
		string getStatus();
		pair<float,float> getInfoPositionA();
		//void setMsgWithIcon(string msg,string color,string icon);
		void setName(string name);
		void setOpponentName(string name);
		int hasName();
		int hasOpponentName();
		string getName();
		string getOpponentName();
		void setPlayerName(string name);
		void sendName(string name);
		void sendAck();
		void makeDraw();
		void sendNameRequest();
		void readyToStart(int localStart);

		TextButton* addCancelButtonCenter();
		TextButton* addCancelButtonLeft();
		TextButton* addCancelButton(pair <int,int> pos);
		~ConnectMenu();
};

