#pragma once

/*
Español:
Una actividad refiere a un estado de los menus del juego en un determinado instante
El contenido de dicho estado se define mediante un archivo .xml que indica
en que lugares se van a encontrar los diferentes objetos graficos
*/
#include <map>
#include <string>
#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\widget.h>
#include <framework\view\allegro_manager\allegro_manager.h>
#include <allegro5\allegro.h>

using namespace std;

class Sysgame;
struct NETWORK_EVENT;

class Controller {
	public:
		Controller(Sysgame *mySysgame);
		
		//void onEvent(ALLEGRO_EVENT *ev) = 0;  // handle ALLEGRO events
		virtual void onCreate() = 0;
		virtual void onNetPack(string &package,map<string,string> &data) = 0;  // handle NETWORK actions
		virtual void onNetEvent(NETWORK_EVENT *ev) = 0;
		virtual ~Controller();
		void addWidget(Widget *w);
		void eraseWidget(string name);
		void callIn(int miliseconds,void(*func)(Sysgame *));
		void disableFlagTimer();
		void addBackgroundImg(string img);
		string getTimerName();
		void callTimerFunc();
		Widget *getWidget(string name);
	protected:
		int flagTimer;
		string timerName;
		Sysgame* mySysgame;
		Viewer* view;
		void(*timerFunc)(Sysgame *);
};