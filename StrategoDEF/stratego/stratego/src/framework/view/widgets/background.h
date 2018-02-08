#pragma once
#include <framework\sysgame\sysgame.h>
#include "widget.h"

typedef unsigned char uc;

class Background : public Widget{
	public:
		Background(Sysgame *sysgame, string name, tuple<uc, uc, uc> color, pair<float, float> pos, pair<float, float> size,bool centered);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		~Background();
};

