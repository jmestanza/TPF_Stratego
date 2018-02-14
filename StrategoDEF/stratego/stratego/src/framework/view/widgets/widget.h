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
		pair<int,int> pos;
		pair<int,int> size;
		string name;
		Viewer* view;
		Sysgame* mySysgame;
		int id;
		bool _killMe;
		bool _beingDrawn;
	public:
		Widget(Sysgame *sys,string name);
		bool getKillMe();
		void killMe();
		pair <float,float> getSize();
		pair <float,float> getPos();

		string getName();
		virtual void handleEvent(ALLEGRO_EVENT *ev) = 0;
		virtual void startDrawing() = 0;
		virtual void stopDrawing() = 0;
		void callStartDrawing();
		void callStopDrawing();

		void setPosSize(pair<int,int> _pos,pair <int,int> _size,bool centered);
		void setPos(pair<int,int> _pos,bool centered); // set pos when size is already set
		void hide();
		void show();
		bool isHidden();
		bool insideMe(int x,int y);
		virtual ~Widget();
		Viewer *getViewer();
		Sysgame *getSysgame();
};

#endif
