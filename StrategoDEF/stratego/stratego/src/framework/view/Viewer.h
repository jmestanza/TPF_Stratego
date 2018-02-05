#pragma once
#ifndef VIEWER_H
#define VIEWER_H

#include <map>
#include <vector>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
using namespace std;

class ViewerException : logic_error {
	public:
		ViewerException(string err);
		string what();
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
		map <string, ALLEGRO_BITMAP*> loaded; // imagenes CARGADAS
		map <string,ShowObject> frontShow; // imagenes MOSTRADAS en pantalla
		vector <string> drawOrder; // orden de muestra en pantalla
	public:
		Viewer();
		void load(string dir, string name); // directorio: de donde cargo la imagen name: nombre asignado de acceso
		void show(string imageName,string showName, float x, float y); // informar que se dibujara una imagen precargada efectivamente en la pantalla
		void destroy(string showName); // borrar imagen de la pantalla
		void draw();
		void changeShowImg(string showName, string newImageName);
		
		~Viewer();
};

#endif

