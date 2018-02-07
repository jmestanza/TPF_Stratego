#pragma once

#include "Widget.h"

class TableButton :Widget
{
public:
	TableButton::TableButton(string _def_img, pair<float, float> _pos, pair<float, float> _size, Sysgame * sys,string _name);
	string default_img;
	void TableButton::handleEvent(ALLEGRO_EVENT *ev);

	~TableButton();
};

