#pragma once


#include <map>
#include <framework\view\widgets\widget.h>
#include "allegro5\allegro.h"

using namespace std;

class Widget;
class Sysgame;

class UI {
	private:
		map <string, Widget*> widgets;
	public:
		UI();
		void loadFromXML(string filename);
		void eraseAll();
		bool AddWidget(Widget* widget, string WidgetName);
		void HandleEvent(ALLEGRO_EVENT *ev);
		void RemoveWidget(string WidgetName);

		~UI();
};

