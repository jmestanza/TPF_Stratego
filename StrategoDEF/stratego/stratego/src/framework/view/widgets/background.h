#pragma once
#include <framework\sysgame\sysgame.h>
#include "widget.h"

/*
Background: Representa una imagen que se muestra en la pantalla, es un widget pasivo al igual que animation,
(No tiene callbacks que se activan cuando suceden cosas)
*/

typedef unsigned char uc;

class Background : public Widget{
	private:
		ALLEGRO_COLOR color;
		int centered;
		string code;
		string myImg;
		string loadImg;
	public:
		Background(Sysgame *sysgame, string name);
		void handleEvent(ALLEGRO_EVENT *ev);
		void configure(string color,pair<float,float> pos,pair<float,float> size,bool _centered);
		void configureImg(string _name,pair<float,float> pos,bool _centered);
		void configureImg(string _name);
		void startDrawing();
		void stopDrawing();
		~Background();
};

