#pragma once

#include "widget.h"

class TextInput : public Widget{
	private:
		string code;
		int _iconShown;
		int _startDraw;
	public:
		TextInput(Sysgame *sys, string name);
		void handleEvent(ALLEGRO_EVENT *ev);
		void configure(pair<float, float> pos,bool centered);
		void addIcon(string imgCode);

		void startDrawing();
		void stopDrawing();

		~TextInput();
};

