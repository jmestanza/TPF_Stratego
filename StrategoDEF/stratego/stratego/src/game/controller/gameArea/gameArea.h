#pragma once

#include <game\model\stratego_engine\BasicToken.h>
#include <game\model\stratego_engine\Player.h>
#include <framework\controller\controller.h>
#include <framework\sysgame\sysgame.h>

class gameArea : Controller{
	private:
		string name,opponentName;
		int localStart;
		Widget *infoAreaA,*infoAreaB;
		string selectedItem;
		string status;
		string mode;
		int tokensToPlace;
		int halfPoint;
		int quarterPoint;
		int threeQuartersPoint;

		int startButtonPresent;
		int optionButtonPresent;

		int animationAdded;
		int waitingMsgAdded;
		int hasOk;

		Player *gameEngine;

	public:
		gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart,string mode);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data) ;  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev) ;

		void setInfoAreaWidgets(Widget *a,Widget *b);
		void eraseInfoAreaWidgets();
		void setSelectedItem(string value);
		void decTokens();
		void incTokens();
		void updateTokenMsg();
		void addStartButton();
		void removeStartButton();
		void addOptionsButtons();
		void removeOptionsButtons();

		void takeOffTokens();
		void randomTokenPlace();
		bool getIStart();
		void setTokenLeft(int value);
		void setRandomPieces();
		void addAnimation();
		void removeAnimation();
		void setStatus(string status);
		void addWaitingMsg(string msg);
		void removeWaitingMsg();
		void updateTurn(pair <int,int> mv , pair<int,int> dst); /// Update table about what happened in turn
		void loadEngineContent(vector <vector <string>> &content);
		Player *getGameEngine();
		string getStatus();
		void tokenReady();
		pair<int,int> convertPosToGeneralType(pair<int,int> original);

		string getSelectedItem();

		~gameArea();
};

