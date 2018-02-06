#pragma once
#include "ShowObject.h"

class ShowImage : public ShowObject{
	public:
		ShowImage();
		void setImage(ALLEGRO_BITMAP *image);
		void draw();
		~ShowImage();
	private:
		ALLEGRO_BITMAP *image;
};

