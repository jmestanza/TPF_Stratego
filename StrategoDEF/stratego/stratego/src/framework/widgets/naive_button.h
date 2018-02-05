#pragma once
#ifndef NAIVEBUTTON_H
#define NAIVEBUTTON_H

#include "Widget.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <framework\view\Viewer.h>

using namespace std;

class NaiveButton : Widget{
	private:
		string img_a,img_b;
		string myViewName;
		void(*onClick)();
	public:
		NaiveButton(Viewer *view,pair<float,float> position,int centered,string img_a,string img_b);
		//void ON
		void handleEvent(ALLEGRO_EVENT *ev);
		~NaiveButton();
};

#endif