#pragma once

/*
GUI
Se encarga de administrar los distintos atributos graficos que se muestran en la pantalla que interactuan
con las acciones del usuario. Es Parte de la vista del juego. Los distintos Widgets que el GUI contiene
llaman a callbacks del controller, que administra que modificar del modelo o de la interfaza grafica
ante las acciones.
*/
#include <map>
#include <framework\view\widgets\widget.h>
#include "allegro5\allegro.h"

using namespace std;

class Widget;
class Sysgame;

class UIException : public exception {
	private:
		string err;
	public:
		UIException(string err);
		virtual const char *what() const throw();
};

class UI {
	private:
		map <string, Widget*> widgets;
		vector <string> deadWidgets;
		vector <Widget*> addWidgets;
	public:
		UI();
		void eraseAll();
		void refreshDead();
		void AddWidget(Widget* widget);
		void HandleEvent(ALLEGRO_EVENT *ev);
		void RemoveWidget(string WidgetName);
		Widget *getWidget(string name);

		~UI();
};

