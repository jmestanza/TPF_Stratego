#include "showImage.h"



ShowImage::ShowImage(Viewer *_view) : ShowObject(_view) {}

void ShowImage::setImage(ALLEGRO_BITMAP *img) {
	image = img;
}
void ShowImage::draw() {
	al_draw_bitmap(image,pos.first,pos.second, 0);
}
ShowImage::~ShowImage() {
	
}
