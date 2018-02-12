#pragma once

#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\widget.h>

class ShowTime : public Widget{
	public:
		ShowTime(Sysgame *sys,string name);
		void configure(string font,string color,pair<float,float> pos,int centered);
		void setTarget(int miliseconds);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void showMillis();
		void showMinutes();
		void onTime( void(*func)(Sysgame*) );
		int timeDone();
		~ShowTime();
	private:
		long long targetTime;
		int _showMiliSeconds;
		int _showMinutes;
		void computeTimeLeft(int &,int &,int &);
		void addCharData(string val,int width,int height,ALLEGRO_FONT* font,ALLEGRO_COLOR color);
		int _baseWidth;
		int _zeroComplete;
		string getStr(int val);
		void(*onTimeFunction)(Sysgame *);

		string myCode;
		map<string,string> letterCodes;
		vector <string> currentlyShowing; // 
};

