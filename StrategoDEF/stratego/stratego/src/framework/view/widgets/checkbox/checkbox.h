#pragma once

#include <framework\view\widgets\widget.h>

class Checkbox : public Widget{
	private:
		int _status;
		string imgA,imgB;
		int mx,my;

		void(*onTickFunction)(Sysgame *,int);
		
	public:
		int getStatus();
		Checkbox(Sysgame *sys,string name);
		void configure(string imgA,string imgB,pair<int,int> pos,bool centered);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void onTick(void (*func)(Sysgame*,int));

		~Checkbox();
};

