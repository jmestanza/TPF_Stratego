#pragma once
#ifndef NAIVEBUTTON_H
#define NAIVEBUTTON_H

#include "Widget.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <framework\view\allegro_manager\allegro_manager.h>

using namespace std;

class NaiveButton : public Widget{
	private:
		string img_a,img_b,img_c;
		string myViewName;
		void(*onClick)();
	public:
		NaiveButton(Sysgame *sys, string name);
		void start(pair<float, float> _pos, int centered, string _img_a, string _img_b, string _img_c);
		//void ON
		void handleEvent(ALLEGRO_EVENT *ev);
		virtual ~NaiveButton();
};

#endif