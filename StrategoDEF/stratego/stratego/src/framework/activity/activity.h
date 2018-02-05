#pragma once

/*
Español:
Una actividad refiere a un estado de los menus del juego en un determinado instante
El contenido de dicho estado se define mediante un archivo .xml que indica
en que lugares se van a encontrar los diferentes objetos graficos
*/
#include <string>
#include <framework\sysgame\sysgame.h>
#include <allegro5\allegro.h>

using namespace std;

class Activity {
	
	public:
		Activity(sysgame *mySysgame);
		void loadContent(string file); // load content from xml file
		virtual void onCreate() = 0; // what to do when we create activity
		// in this function we will widgets actions
		virtual void onEvent(ALLEGRO_EVENT *ev) = 0;  // handle events
	private:
		sysgame * mySysgame;
};