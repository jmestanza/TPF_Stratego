#include "showImage.h"



ShowImage::ShowImage() {}

void ShowImage::setImage(ALLEGRO_BITMAP *img) {
	image = img;
}
void ShowImage::draw() {
	al_draw_bitmap(image,pos.first,pos.second, 0);
}
ShowImage::~ShowImage() {
	
}
