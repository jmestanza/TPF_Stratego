#pragma once

#include "widget.h"


class screenText : public Widget{
	private:
		string code;
		int created;
		int centered_mode;
		pair <int,int> centeredPosition;

		string myFont;
		ALLEGRO_COLOR myColor;
		int flagDraw;
		int cnt;
	public:
		screenText(Sysgame *sys,string name);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void configure(string text,string font,ALLEGRO_COLOR color,pair<float,float> pos,int centered);
		void configure(string text,string font,ALLEGRO_COLOR color);
		void changeMsg(string text);

		~screenText();
};

