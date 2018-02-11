#include "screen_text.h"
#include <framework\utils\random_number.h>


screenText::screenText(Sysgame *sys,string name) : Widget(sys,name){
	code = to_string(randomNumber());
	created = 0;
}

void screenText::configure(string msg, string font, ALLEGRO_COLOR color,pair<float,float> _pos,int centered) {
	//ALLEGRO_BITMAP *a = al_create_bitmap(width,height);
	configure(msg,font,color);
	pos = _pos;
	
	if (centered) {
		pos.first -= size.first/2;
		pos.second -= size.second/2;
	}
	created = 1;
}
void screenText::configure(string msg,string font,ALLEGRO_COLOR color) {
	if (created) view->eraseLoaded("screen_text_img_" + code);
	ALLEGRO_FONT *alFont = view->getFont(font);

	int bbx,bby,bbw,bbh;
	al_get_text_dimensions(alFont,
		msg.c_str(),
		&bbx,&bby,&bbw,&bbh);

	float width = bbw;
	float height = bbh;
	ALLEGRO_BITMAP *mySurface = al_create_bitmap(bbw,bbh);
	al_set_target_bitmap(mySurface);
	al_draw_text(alFont,
		color,-bbx,-bby,ALLEGRO_ALIGN_LEFT,
		msg.c_str());
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
	getViewer()->loadFromBitmap(mySurface,"screen_text_img_" + code);
	size = pair<float,float>(width,height);
}
void screenText::startDrawing() {
	view->show("screen_text_img_"+code,"screen_text_img_" + code,this->pos.first,this->pos.second);
}
void screenText::stopDrawing() {
	view->stopShow("screen_text_img_"+code);
}
void screenText::handleEvent(ALLEGRO_EVENT *ev) {

}
screenText::~screenText() {

}
