#pragma once

#include <vector>
#include <allegro5/allegro.h>
using namespace std;

class ShowObject {
/**ShowObject:
	representa una objeto grafico actualmente mostrado en pantalla**/
	protected:
		bool sizeSet;
		pair<float, float> pos,size;
	public:
		ShowObject();
		~ShowObject();
		void setSize(pair<float, float> size);
		void setPosition(pair<float, float> pos,bool centered);
		virtual void draw() = 0;
};
