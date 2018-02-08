#pragma once

#include "Widget.h"

class TableButton : public Widget
{
public:
	TableButton(string _def_img, pair<float, float> _pos, pair<float, float> _size, Sysgame * sys,string _name);
	string default_img;
	void handleEvent(ALLEGRO_EVENT *ev);

	void startDrawing();

	~TableButton();
};

