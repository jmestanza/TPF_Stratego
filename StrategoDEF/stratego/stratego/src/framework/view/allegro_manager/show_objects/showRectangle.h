#pragma 

#include <allegro5\drawing.h>
#include <allegro5/allegro_primitives.h>
#include "ShowObject.h"

class ShowRectangle : public ShowObject{
	private:
		ALLEGRO_COLOR color;
		float thickness;
	public:
		ShowRectangle();
		void setColor(unsigned char r,unsigned char g,unsigned char b);
		void draw();
		~ShowRectangle();
};

