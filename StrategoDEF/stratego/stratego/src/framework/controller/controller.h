#pragma once


#include <map>
#include <string>
#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\widget.h>
#include <framework\view\allegro_manager\allegro_manager.h>
#include <allegro5\allegro.h>

using namespace std;

class Sysgame;
struct NETWORK_EVENT;

/*
En este archivo se encuentra programado el Controller que es 
la clase que administra como coloar los distintos objetos graficos, como hacerlos
interactuar entre si, y contra el network y el motor de juego (cosiderados el modelo)

La idea fundamental de framework es que permita que en el GAME se haga heredar 
cada controller particular de cada parte del juego del controller generico y se sobre-escriban asi
las funciones generales que todo controller debe tener.

*/

class Controller {
	public:
		Controller(Sysgame *mySysgame);
		
		virtual void onCreate() = 0; //se llama cuando el controller se establece
		virtual void onNetPack(string &package,map<string,string> &data) = 0;  // que hacer cuando llega un packete
		virtual void onNetEvent(NETWORK_EVENT *ev) = 0; // que hacer cuando sucede algo importante con respecto a la conexion
		virtual ~Controller();
		void addWidget(Widget *w); /// agregar un widget a la interfaz grafico
		void eraseWidget(string name);
		void callIn(int miliseconds,void(*func)(Sysgame *)); /// llamar un callback en X milisegundos
		void disableFlagTimer();
		void addBackgroundImg(string img); /// agregar un fondo a lo que ve el usuario
		string getTimerName(); /// cuando se usa un timer que nombre tiene en la ui dicho timer
		void callTimerFunc(); /// llamar a la funcion callback de un timer
		Widget *getWidget(string name); /// conseguir un widget
	protected:
		int flagTimer;
		string timerName;
		Sysgame* mySysgame;
		Viewer* view;
		void(*timerFunc)(Sysgame *); /// la funcion callback del timer
};