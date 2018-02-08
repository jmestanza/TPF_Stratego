#pragma once
#include "ShowObject.h"


class Viewer;
class ShowObject;

class ShowImage : public ShowObject{
	public:
		ShowImage(Viewer *_view);
		void setImage(ALLEGRO_BITMAP *image);
		void draw();
		~ShowImage();
	private:
		ALLEGRO_BITMAP *image;
};

