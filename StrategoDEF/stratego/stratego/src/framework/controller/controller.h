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
#include <allegro5\allegro.h>

using namespace std;

class Sysgame;
struct NETWORK_EVENT;

class Controller {
	public:
		Controller(Sysgame *mySysgame);
		// in this function we will widgets actions
		virtual void onEvent(ALLEGRO_EVENT *ev) = 0;  // handle ALLEGRO events
		virtual void onNetPack(string &package,map<string,string> &data) = 0;  // handle NETWORK actions
		virtual void onNetEvent(NETWORK_EVENT *ev) = 0;

	private:
		Sysgame* mySysgame;
};