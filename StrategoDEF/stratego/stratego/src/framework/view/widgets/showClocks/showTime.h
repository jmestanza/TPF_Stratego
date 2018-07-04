#pragma once

/*
Un showclock es un timer que muestra segundos, minutos, milisegundos en la pantalla
y llama un callback cuando se vence el contrareloj

Por el momento incluso se utiliza para timers que no se ven en la pantalla, aunque 
queda pendiente que esto no se haga con un timer grafico que se muestra en un lugar no visible de la pantalla
*/
#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\widget.h>

class ShowTime : public Widget{
	public:
		ShowTime(Sysgame *sys,string name);
		void configure(string font,string color,pair<float,float> pos,int centered);
		void setTarget(int miliseconds); // Setear cantidad de tiempo del contrareloj
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
		bool _isBeingDrawn;

		string myCode;
		map<string,string> letterCodes;
		vector <string> currentlyShowing; 
};

