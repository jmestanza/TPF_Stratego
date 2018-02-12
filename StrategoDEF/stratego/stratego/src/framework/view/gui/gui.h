#pragma once


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
		void loadFromXML(string filename);
		void eraseAll();
		void refreshDead();
		void AddWidget(Widget* widget);
		void HandleEvent(ALLEGRO_EVENT *ev);
		void RemoveWidget(string WidgetName);
		Widget *getWidget(string name);

		~UI();
};

