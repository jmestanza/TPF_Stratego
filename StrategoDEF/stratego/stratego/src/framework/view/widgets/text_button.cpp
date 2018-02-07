#include "text_button.h"



textButton::textButton(Sysgame* sys,string name) : NaiveButton(sys,name) {
	
}
void textButton::generate(string msg, imgGroup img) {
	ALLEGRO_BITMAP *a = mySysgame->getAllegroHandler()->getImg(img.img_a);
	ALLEGRO_BITMAP *b = mySysgame->getAllegroHandler()->getImg(img.img_b);
	ALLEGRO_BITMAP *c = mySysgame->getAllegroHandler()->getImg(img.img_c);


}


textButton::~textButton() {}
