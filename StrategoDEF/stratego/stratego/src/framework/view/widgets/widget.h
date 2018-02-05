#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include <framework\view\allegro_manager\allegro_manager.h>
#include <string>
#include <allegro5\allegro.h>
using namespace std;

class Widget {
	protected:
		pair<float, float> pos;
		string name;
		Viewer* view;
		int id;
	public:
		Widget(Viewer *_view);
		virtual void handleEvent(ALLEGRO_EVENT *ev) = 0;
		~Widget();
};

#endif
