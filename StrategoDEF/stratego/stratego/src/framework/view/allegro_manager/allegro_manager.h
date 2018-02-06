#pragma once
#ifndef VIEWER_H
#define VIEWER_H

#include <map>
#include <vector>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
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
		ALLEGRO_DISPLAY * display;
		pair <float, float> screenSize;

		map <string, ALLEGRO_BITMAP*> loaded; // imagenes CARGADAS
		map <string,ShowObject*> frontShow; // imagenes MOSTRADAS en pantalla
		vector <string> drawOrder; // orden de muestra en pantalla
		bool _exit;
		ALLEGRO_EVENT_QUEUE *q;
		bool _debug;
	public:
		Viewer();
		pair<float,float> getScreenSize();
		void setDebugFlag();
		void loadConfFile(string xmlFile);
		void start();
		void load(string dir, string name); // directorio: de donde cargo la imagen name: nombre asignado de acceso
		void show(string imageName,string showName, float x, float y); // informar que se dibujara una imagen precargada efectivamente en la pantalla
		void showRectangle(string showName,unsigned char r,unsigned char g,unsigned char b,pair<float,float> pos,pair<float,float> size,bool centered);
		void stopShow(string showName); // borrar imagen de la pantalla
		void draw();
		void changeShowImg(string showName, string newImageName);
		void destroyAll(); // empty screen
		bool getNextEvent(ALLEGRO_EVENT *ev);

		~Viewer();
};

#endif
