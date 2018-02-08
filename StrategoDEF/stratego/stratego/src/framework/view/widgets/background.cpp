#include "background.h"


Background::Background(Sysgame *sysgame,string name,tuple<uc,uc,uc> color,pair<float,float> pos,pair<float,float> size,bool centered) : Widget(sysgame,name){
	uc r = get<0>(color), g = get<1>(color), b = get<2>(color);
	mySysgame->getAllegroHandler()->showRectangle(name,r,g,b,pos,size,centered);
}

void Background::handleEvent(ALLEGRO_EVENT *ev) {

}
void Background::startDrawing() {

}
Background::~Background() {
	mySysgame->getAllegroHandler()->stopShow(name);
}
