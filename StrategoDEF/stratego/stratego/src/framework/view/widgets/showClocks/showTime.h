#pragma once

#include <framework\view\widgets\widget.h>

class ShowTime : public Widget{
	public:
		ShowTime(Sysgame *sys,string name);
		void configure(string font,string color,pair<float,float> pos,int centered);
		void setTarget(int miliseconds);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		~ShowTime();
	private:
		long long targetTime;
		int _showMiliSeconds;
};

