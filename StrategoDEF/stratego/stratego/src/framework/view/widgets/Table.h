#pragma once

#include <framework\view\allegro_manager\allegro_manager.h>
#include <framework\sysgame\sysgame.h>
#include "widget.h"
#include "TableButton.h"
#include <iostream>

#define TABLE_SLOTS 10

enum { IDLE, BUTTON_DOWN, BUTTON_UP };

using namespace std;

class TableException : public exception {
private:
	string err;
public:
	TableException(string er);
		virtual const char *what() const throw();

};

class Table : Widget
{
public:
	//Table(Viewer* _view, pair <float,float> screen_center, pair<float, float>_pieceSize);
	Table(Sysgame*Sys, string _name,string _img_a,string _img_b, pair<float, float> _screen_center, pair<float, float>_pieceSize);
	int status;
	string img_a;
	string img_b;
	pair<float,float> fakesize;
	pair<float,float> screen_center;
	vector<TableButton> t_table;
	map<pair<int, char>, int> ind_table;

	pair<int, char> WhoIsInRange(pair<float, float> _mousepos);
	void handleEvent(ALLEGRO_EVENT *ev);
	void startDrawing();
	~Table();
};

