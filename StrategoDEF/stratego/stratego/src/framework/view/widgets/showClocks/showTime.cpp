#include "showTime.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>
#include <framework\utils\random_number.h>
#include <framework\utils\getMillisFromEpoch.h>
#include <framework\view\utils\copyBitmap.h>

ShowTime::ShowTime(Sysgame *sys,string name) : Widget(sys,name) {
	string myCode = "show_timer_"+to_string(randomNumber());
}

void ShowTime::configure(string font,string color,pair<float,float> pos,int centered) {

	ALLEGRO_FONT* currentFont = view->getFont(font);
	ALLEGRO_COLOR currentColor = view->getColor(color);

	for (int i = 0;i < 10;i++) { /// generate numbers
		// = al_create_bitmap(;
		int bbx,bby,bbw,bbh;
		al_get_text_dimensions(currentFont,to_string(i).c_str(),&bbx,&bby,&bbw,&bbh);

		ALLEGRO_BITMAP* aux = al_create_bitmap(bbx+bbw,bby+bbh);
		al_set_target_bitmap(aux);
		al_draw_text(currentFont,currentColor,0,0,0,to_string(i).c_str());
	}
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));


}
void ShowTime::setTarget(int miliseconds) {
	long long targetTime = getMillisFromEpoch() + miliseconds;
	//targetTime = 
}
void ShowTime::handleEvent(ALLEGRO_EVENT *ev) {

}
void ShowTime::startDrawing() {

}
void ShowTime::stopDrawing() {

}

ShowTime::~ShowTime() {}
