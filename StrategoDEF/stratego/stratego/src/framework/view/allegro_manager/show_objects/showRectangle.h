#pragma once
#include "ShowObject.h"
#include <allegro5\drawing.h>
#include <allegro5\allegro_primitives.h>


class ShowObject;
class Viewer;

class ShowRectangle : public ShowObject{
	private:
		ALLEGRO_COLOR color;
		float thickness;
	public:
		ShowRectangle(Viewer *view);
		void setColor(unsigned char r,unsigned char g,unsigned char b);
		void draw();
		~ShowRectangle();
};

