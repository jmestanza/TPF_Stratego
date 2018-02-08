#include "showRectangle.h"


ShowRectangle::ShowRectangle(Viewer *_view) : ShowObject(_view) {
}

void ShowRectangle::draw() {
	float x1 = pos.first , y1 = pos.second;
	float x2 = x1 + size.first , y2 = y1 + size.second;
	//al_get_target_bitmap()
	al_draw_filled_rectangle(x1,y1,x2,y2,color);
}
void ShowRectangle::setColor(unsigned char r, unsigned char g, unsigned char b) {
	color = al_map_rgb(r,g,b);
}

ShowRectangle::~ShowRectangle() {}
