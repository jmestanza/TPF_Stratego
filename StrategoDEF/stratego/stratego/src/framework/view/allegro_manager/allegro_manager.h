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

using namespace std;

class AllegroHandlerException : public exception {
	private:
		string err;
	public:
		AllegroHandlerException(string err);
		virtual const char *what() const throw();
};

class ShowObject {
	/**ShowObject:
		representa una imagen actualmente mostrada en pantalla
	*/
	public:
		pair<float, float> pos;
		ALLEGRO_BITMAP *bitmap;
		ShowObject() { }
		ShowObject(ALLEGRO_BITMAP* _bitmap,float x, float y) : bitmap(_bitmap) {
			pos = pair<float, float>(x, y);
		}
};

/*
Viewer: ultima interfaz que organiza los distintos graficos
mostrados en pantalla en pantalla
*/
class Viewer {
	private:
		ALLEGRO_DISPLAY * display;
		pair <int, int> screenSize;

		map <string, ALLEGRO_BITMAP*> loaded; // imagenes CARGADAS
		map <string,ShowObject> frontShow; // imagenes MOSTRADAS en pantalla
		vector <string> drawOrder; // orden de muestra en pantalla
		bool _exit;
		ALLEGRO_EVENT_QUEUE *q;
	public:
		Viewer();
		void loadConfFile(string xmlFile);
		void start();
		void load(string dir, string name); // directorio: de donde cargo la imagen name: nombre asignado de acceso
		void show(string imageName,string showName, float x, float y); // informar que se dibujara una imagen precargada efectivamente en la pantalla
		void destroy(string showName); // borrar imagen de la pantalla
		void draw();
		void changeShowImg(string showName, string newImageName);
		void destroyAll(); // empty screen
		bool getNextEvent(ALLEGRO_EVENT *ev);

		~Viewer();
};

#endif

