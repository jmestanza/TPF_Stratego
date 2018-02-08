#pragma once
#ifndef NAIVEBUTTON_H
#define NAIVEBUTTON_H

#include "Widget.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <framework\view\allegro_manager\allegro_manager.h>

using namespace std;

class NaiveButton : public Widget{
	protected:
		string img_a,img_b,img_c;
		string myViewName;
		int mx,my;
		void(*onClickFunction)(Sysgame *);
		int _clicked;
	public:
		NaiveButton(Sysgame *sys, string name);
		void start(pair<float, float> _pos, int centered, string _img_a, string _img_b, string _img_c);
		//void ON
		void onClick(void(*func)(Sysgame *));

		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		virtual ~NaiveButton();
};

#endif