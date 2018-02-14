#include "showImage.h"



ShowImage::ShowImage(Viewer *_view) : ShowObject(_view) {}

void ShowImage::setImage(ALLEGRO_BITMAP *img) {
	image = img;
	this->setSize(pair<float,float>(al_get_bitmap_width(img),al_get_bitmap_height(img)));
}
void ShowImage::draw() {
	al_draw_bitmap(image,pos.first,pos.second, 0);
}
ShowImage::~ShowImage() {
	
}
