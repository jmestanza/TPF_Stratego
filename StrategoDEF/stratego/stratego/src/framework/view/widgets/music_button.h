#pragma once
#include "widget.h"
class music_button : public Widget {
private:
	pair<float,float>pos;
public:
	string myviewname;
	string image_name;
	Sysgame* mySys; 
	void(*onClickFunction)(Sysgame *);
	music_button(Sysgame * sys,pair<float,float>,string name,string );
	void handleEvent(ALLEGRO_EVENT *ev);
	void stopDrawing();
	void startDrawing();
	void onClick(void(*func)(Sysgame *));
	bool insideIconRange(int,int);
	~music_button();
};

