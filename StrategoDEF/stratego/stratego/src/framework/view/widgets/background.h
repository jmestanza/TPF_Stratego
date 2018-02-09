#pragma once
#include <framework\sysgame\sysgame.h>
#include "widget.h"

typedef unsigned char uc;

class Background : public Widget{
	private:
		ALLEGRO_COLOR color;
		int centered;
		string code;
	public:
		Background(Sysgame *sysgame, string name);
		void handleEvent(ALLEGRO_EVENT *ev);
		void configure(string color,pair<float,float> pos,pair<float,float> size,bool _centered);
		void startDrawing();
		void stopDrawing();
		~Background();
};

