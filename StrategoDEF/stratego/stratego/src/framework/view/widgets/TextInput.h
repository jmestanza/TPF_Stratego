#pragma once

#include "widget.h"

/// Nota, para correcto funcionamiento se debe llamar a configure y a AddIcon
/// Aunque no tenga icono el text input

class TextInput : public Widget{
	private:
		string code;
		string shownText;

		int _iconShown;
		int _startDraw;
		bool flagChange;
		int startPointX,startPointY;
		string smallFont;
		string myDefaultFont;
		int auxCount; /// timer auxiliar
		int _showTile;
		int _smallTextAdded;
		string smallTextName;
		int smallTextX,smallTextY;
		bool _enabled;
	public:
		TextInput(Sysgame *sys, string name);
		string getText();
		void enable();
		void disable();

		void handleEvent(ALLEGRO_EVENT *ev);
		void configure(pair<float, float> pos,bool centered);
		void addIcon(string imgCode);
		void addSmallText(string msg);
		void updateDrawing();
		void startDrawing();
		void stopDrawing();
		void setText(string text);

		~TextInput();
};

