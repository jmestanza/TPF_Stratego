#pragma once

#include "widget.h"

/*
//Text input es una entidad que permita que se le escriba texto, el controller luego puede
// acceder al contenido escrito
*/


/* Nota, para correcto funcionamiento se debe llamar a configure y a AddIcon
 Aunque no tenga icono el text input

Nota: Se deja como pendiente que el funcionamiento no sea de manera tan rebuscada*/

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
		void addIcon(string imgCode); // agregar icono del text input
		void addSmallText(string msg); // agregar pequenio texto que se muestra en la esquina
		void updateDrawing();
		void startDrawing();
		void stopDrawing();
		void setText(string text); // configurar que texto muestra

		~TextInput();
};

