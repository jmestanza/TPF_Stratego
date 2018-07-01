#pragma once

/*
Estas clases: ShowObject, showRectangle, showImage estructuran las distintas
entidades que representan los objetos mostrados en la pantalla.
Inicialmente se penso que era buena idea poner muchos tipos de cosas, pero
finalmente se termino utilizando solo ShowImages y en todo caso si se quiere mostrar un rectangulo 
pintado, un texto, se genera un bitmap, y se muestra como showImage.

Por lo tanto queda como pendiente eliminar showObject, showRectangle y solo utilizar showImage, 
por una razon de compatibilidad no se realizo aun la modificacion, pero es una tarea pendiente.
El proyecto en prinicpio utiliza solamente showImages, ya que se considera demasiado rebuscado
hacer demasiados tipos de entidades de elementos graficos mostrados en la pantalla, con solo bitmaps
es suficiente.
*/

#include <vector>
#include <allegro5/allegro.h>

using namespace std;

class Viewer;


class ShowObject {
/**ShowObject:
	representa una objeto grafico actualmente mostrado en pantalla**/
	protected:
		bool sizeSet;
		pair<float, float> pos,size;
		Viewer *view;

	public:
		ShowObject(Viewer *_view);
		~ShowObject();
		
		void setSize(pair<float, float> size);
		void setPosition(pair<float, float> pos,bool centered);
		virtual void draw() = 0;
};
