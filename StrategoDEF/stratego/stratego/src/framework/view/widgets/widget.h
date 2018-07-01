#pragma once
#ifndef WIDGET_H
#define WIDGET_H

/*
Widget: representa un objeto grafico de la pantalla que reacciona ante eventos del usuario
Es parte de la vista, ya que forma parte de la interfaz grafica. La idea fundamental es que los
distintos Widget activen callbacks ante los eventos del usuario, que el controller utilize para
decidir que hacer con el juego.
*/

#include <framework\view\allegro_manager\allegro_manager.h>
#include <string>
#include <allegro5\allegro.h>
using namespace std;

class Sysgame;

class Widget {
	protected:
		pair<int,int> pos;
		pair<int,int> size;
		string name;
		Viewer* view;
		Sysgame* mySysgame;
		int id;
		bool _killMe;
		bool _beingDrawn;
	public:
		Widget(Sysgame *sys,string name);
		bool getKillMe(); // Revisar si el widget esta en la cola de destruccion 
		void killMe(); // Cargar el widget para la cola de destruccion
		pair <float,float> getSize();
		pair <float,float> getPos();

		string getName();
		virtual void handleEvent(ALLEGRO_EVENT *ev) = 0; // Cada widget reacciona distinto ante eventos
		virtual void startDrawing() = 0; // Comenzar a dibujar widget
		virtual void stopDrawing() = 0; // Dejar de dibujar widget
		void callStartDrawing(); // Funcion auxiliar
		void callStopDrawing();

		void setPosSize(pair<int,int> _pos,pair <int,int> _size,bool centered);
		void setPos(pair<int,int> _pos,bool centered); // set pos when size is already set
		void hide();
		void show();
		bool isHidden();
		bool insideMe(int x,int y); // Ver si el mouse esta dentro del widget
		virtual ~Widget();
		Viewer *getViewer();
		Sysgame *getSysgame();
};

#endif
