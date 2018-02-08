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
		pair<float, float> size;
		string name;
		Viewer* view;
		Sysgame* mySysgame;
		int id;
		bool _killMe;
	public:
		Widget(Sysgame *sys,string name);
		bool getKillMe();
		void killMe();

		string getName();
		virtual void handleEvent(ALLEGRO_EVENT *ev) = 0;
		virtual void startDrawing() = 0;
		virtual void stopDrawing() = 0;
		virtual ~Widget();
		Viewer *getViewer();
		Sysgame *getSysgame();
};

#endif
