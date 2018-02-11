#pragma once

#include "widget.h"


class screenText : public Widget{
	private:
		string code;
	public:
		screenText(Sysgame *sys,string name);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void configure(string text,string font,ALLEGRO_COLOR color,pair<float,float> pos,int centered);

		~screenText();
};

