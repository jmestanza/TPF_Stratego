
#include "text_button.h"

#include <allegro5\allegro_primitives.h>
#include <framework\utils\random_number.h>

imgGroup::imgGroup(string _a,string _b,string _c) : img_a(_a),img_b(_b),img_c(_c) {

}
textButton::textButton(Sysgame* sys,string name) : NaiveButton(sys,name) {
	n1 = randomNumber();
	n2 = randomNumber();
	n3 = randomNumber();
}

void blitCentered(ALLEGRO_FONT *font,string msg,ALLEGRO_COLOR color,ALLEGRO_BITMAP *bitmap) {
	al_set_target_bitmap(bitmap);
	float width = al_get_bitmap_width(bitmap);
	float height = al_get_bitmap_height(bitmap);
	int bbx,bby,bbw,bbh;

	al_get_text_dimensions(font,
		msg.c_str(),
		&bbx,&bby,&bbw,&bbh);

	al_draw_text(font,
		al_map_rgb(255,255,255), int(width / 2.0),int(height / 2.0- (bbh+bby)/2.0-2.0) ,ALLEGRO_ALIGN_CENTRE,
		msg.c_str());
}
void textButton::generate(string msg, imgGroup img , pair<float,float> pos,int centered) {


	float width = al_get_bitmap_width(getSysgame()->getAllegroHandler()->getImg(img.img_a));
	float height = al_get_bitmap_height(getSysgame()->getAllegroHandler()->getImg(img.img_a));

	ALLEGRO_BITMAP *a = al_create_bitmap(width,height);
	ALLEGRO_BITMAP *b = al_create_bitmap(width,height);
	ALLEGRO_BITMAP *c = al_create_bitmap(width,height);


	al_set_target_bitmap(a);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_a),0,0,0);//al_create_bitmap(width,height);
	al_set_target_bitmap(b);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_b),0,0,0);
	al_set_target_bitmap(c);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_c),0,0,0);

	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	blitCentered(getViewer()->getFont("roboto_v1"),msg,al_map_rgb(255,255,255),a);
	blitCentered(getViewer()->getFont("roboto_v1"),msg,al_map_rgb(255,255,255),b);
	blitCentered(getViewer()->getFont("roboto_v1"),msg,al_map_rgb(255,255,255),c);
	//cout << n1 << ' ' << n2 << ' ' << n3 << '\n';

	string a_code = "text_button_" + to_string(n1);
	string b_code = "text_button_" + to_string(n2);
	string c_code = "text_button_" + to_string(n3);
	

	getViewer()->loadFromBitmap(a,a_code);
	getViewer()->loadFromBitmap(b,b_code);
	getViewer()->loadFromBitmap(c,c_code);
	

	this->start(pos,centered,a_code,b_code,c_code);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
}


textButton::~textButton() {}
