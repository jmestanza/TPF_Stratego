#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include <framework\view\allegro_manager\allegro_manager.h>
#include <string>
#include <allegro5\allegro.h>
using namespace std;

class Sysgame;

class Widget {
	protected:
		pair<float, float> pos;
		string name;
		Viewer* view;
		Sysgame* mySysgame;
		int id;
	public:
		Widget(Sysgame *sys,string name);
		string getName();
		virtual void handleEvent(ALLEGRO_EVENT *ev) = 0;
		virtual ~Widget();
};

#endif
