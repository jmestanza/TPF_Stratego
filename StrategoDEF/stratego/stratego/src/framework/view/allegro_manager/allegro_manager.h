#pragma once
#ifndef VIEWER_H
#define VIEWER_H

#include <map>
#include <vector>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "show_objects\ShowObject.h"
#include "show_objects\showImage.h"
#include "show_objects\showRectangle.h"


using namespace std;

class AllegroHandlerException : public exception {
	private:
		string err;
	public:
		AllegroHandlerException(string err);
		virtual const char *what() const throw();
};

/*
Viewer: ultima interfaz que organiza los distintos graficos
mostrados en pantalla en pantalla.
La idea fundamental es organizar el orden en el que las cosas se pintan en la pantalla,
cargar las imagenes, musica a la memoria, destruirlas y organizarlas en map<string,string>

LEER ShowObject para ver como se estructuran las entidades que se muestran en la pantalla

*/
class Viewer {
	private:
		pair <float, float> screenSize;

		map <string,ALLEGRO_BITMAP*> loaded; // imagenes CARGADAS
		map <string,ShowObject*> frontShow; // imagenes MOSTRADAS en pantalla

		map<string,ALLEGRO_SAMPLE*> loadedAudio;
		map<string, ALLEGRO_SAMPLE_INSTANCE*> AudioInstances;
		map <string,ALLEGRO_FONT*> fonts;
		map <string, ALLEGRO_COLOR> colors;

		vector <string> drawOrder; // orden de muestra en pantalla
		bool _exit;
		ALLEGRO_DISPLAY * display;
		ALLEGRO_EVENT_QUEUE *q;
		ALLEGRO_TIMER *timer;
		int TimerFreq;

		bool _debug;
	public:
		Viewer();
		pair<float,float> getScreenSize();
		void setScreenSize(pair<float,float> size);
		void setDebugFlag();
		/// cargar archivos de configuracion de todos los recursos graficos del juego
		void loadConfFile(string xmlFile);
		void loadImgFile(string xmlFile);
		void loadAudioFile(string xmlFile);
		void loadFontFile(string xmlFile);
		void loadColorsFile(string xmlFile);
		void start();
		void load(string dir, string name); // directorio: de donde cargo la imagen name: nombre asignado de acceso
		void loadFromBitmap(ALLEGRO_BITMAP *b,string name); // cargar a la memoria una imagen desde un bitmap
		void loadAudio(string dir,string name); // cargar un audio a la memoria
		void loadFont(string dir,string name,int size); // etc
		void loadColor(string code, string name); // ect
		void eraseLoaded(string loadedName); // borrar de la memoria una imagen
		void showBitmaps(); /// pitnar todos los bitmaps en el orden configurado

		ALLEGRO_BITMAP *getImg(string imgName); /// conseguir imagenes, fonts, colores de la memoria
		ALLEGRO_FONT* getFont(string name);
		ALLEGRO_COLOR getColor(string color);

		ALLEGRO_DISPLAY *getScreen();
		
		void show(string imageName,string showName, float x, float y); // informar que se dibujara una imagen precargada efectivamente en la pantalla
		void showRectangle(string showName,unsigned char r,unsigned char g,unsigned char b,pair<float,float> pos,pair<float,float> size,bool centered);
		void playloop(string song);
		void playonce(string song);
		void stopShow(string showName); // borrar imagen de la pantalla
		void draw();
		void changeShowImg(string showName, string newImageName); /// cambiar una imagen mostrada en la pantalla
		void changeShowImgPos(string showName,float x,float y,int centered); /// moverla..
		void destroyAll(); // empty screen
		bool getNextEvent(ALLEGRO_EVENT *ev); // conseguir eventos de allegor
		bool hasLoadedImg(string name); // checkear si una imagen esta cargada en la memoria

		~Viewer();
};

#endif

