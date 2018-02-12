#pragma once

#include <framework\controller\controller.h>
#include <framework\sysgame\sysgame.h>

class gameArea : Controller{
	private:
		string name,opponentName;
		int localStart;
		Widget *infoAreaA,*infoAreaB;
	public:
		gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart);
		void onCreate();
		void onNetPack(string &package,map<string,string> &data) ;  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev) ;

		void setInfoAreaWidgets(Widget *a,Widget *b);
		void eraseInfoAreaWidgets();

		~gameArea();
};

