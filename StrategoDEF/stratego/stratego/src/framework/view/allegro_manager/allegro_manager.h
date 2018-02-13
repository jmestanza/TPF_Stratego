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
mostrados en pantalla en pantalla
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
		void loadConfFile(string xmlFile);
		void loadImgFile(string xmlFile);
		void loadAudioFile(string xmlFile);
		void loadFontFile(string xmlFile);
		void loadColorsFile(string xmlFile);
		void start();
		void load(string dir, string name); // directorio: de donde cargo la imagen name: nombre asignado de acceso
		void loadFromBitmap(ALLEGRO_BITMAP *b,string name);
		void loadAudio(string dir,string name);
		void loadFont(string dir,string name,int size);
		void loadColor(string code, string name);
		void eraseLoaded(string loadedName);

		ALLEGRO_BITMAP *getImg(string imgName);
		ALLEGRO_FONT* getFont(string name);
		ALLEGRO_COLOR getColor(string color);

		ALLEGRO_DISPLAY *getScreen();
		
		void show(string imageName,string showName, float x, float y); // informar que se dibujara una imagen precargada efectivamente en la pantalla
		void showRectangle(string showName,unsigned char r,unsigned char g,unsigned char b,pair<float,float> pos,pair<float,float> size,bool centered);
		void playloop(string song);
		void playonce(string song);
		void stopShow(string showName); // borrar imagen de la pantalla
		void draw();
		void changeShowImg(string showName, string newImageName);
		void destroyAll(); // empty screen
		bool getNextEvent(ALLEGRO_EVENT *ev);
		bool hasLoadedImg(string name);

		~Viewer();
};

#endif

