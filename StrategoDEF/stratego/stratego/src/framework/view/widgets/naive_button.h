#pragma once
#ifndef NAIVEBUTTON_H
#define NAIVEBUTTON_H

// NaiveButton: Wiget basico de boton, cuando se presiona se llama un callback,
// se peude configurar sus imagenes que cambian cuando se presiona.

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
		int _iconMode;
		int _enabled;
	public:
		
		NaiveButton(Sysgame *sys, string name);
		virtual void onClickToOverride();
		virtual void onReleaseToOverride();
		virtual void onHardClickToOverride();

		void start(pair<float, float> _pos, int centered, string _img_a, string _img_b, string _img_c);
		//void ON
		void onClick(void(*func)(Sysgame *));
		

		int enabled();
		void enable();
		void disable();
		void addIcon(string img);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		virtual ~NaiveButton();
};

#endif