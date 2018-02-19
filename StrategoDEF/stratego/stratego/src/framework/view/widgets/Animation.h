#pragma once

/*
Animation: Representa una animacion de pantalla que tiene distinitos bitmaps que avanzan con el timepo

*/
#include <vector>
#include "widget.h"
using namespace std;

class Animation : Widget{
	private:
		int _drawing;
		int _efDrawing;
		vector <string> images;
		string myNameCode;
		int _started;
		
	public:
		Animation(Sysgame *sys,string name);
		void configure(vector <string> _images,pair<float,float> _pos,int centered);
		virtual void handleEvent(ALLEGRO_EVENT *ev);
		virtual void startDrawing();
		virtual void stopDrawing();
		void configure(vector <string> _images);
		void updateDrawing();
		~Animation();
};

