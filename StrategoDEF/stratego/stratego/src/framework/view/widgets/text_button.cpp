
#include "text_button.h"
#include <allegro5/allegro.h>

#include <allegro5\allegro_primitives.h>
#include <framework\utils\random_number.h>
#include <allegro5/allegro_image.h>

imgGroup::imgGroup(string _a,string _b,string _c) : img_a(_a),img_b(_b),img_c(_c) {

}
TextButton::TextButton(Sysgame* sys,string name) : NaiveButton(sys,name) {
	n1 = randomNumber();
	n2 = randomNumber();
	n3 = randomNumber();
}

void blitCentered(ALLEGRO_FONT *font,string msg,ALLEGRO_COLOR color,ALLEGRO_BITMAP *bitmap) {
	int width = al_get_bitmap_width(bitmap);
	int height = al_get_bitmap_height(bitmap);
	int bbx,bby,bbw,bbh;

	al_get_text_dimensions(font,
		msg.c_str(),
		&bbx,&bby,&bbw,&bbh);

	int px = (width / 2 - (bbx + bbw) / 2);
	int py = (height / 2 - (bby + bbh) / 2) - 2;
	//px = px / 5 * 5;
	//py = py / 5 * 5;
	//cout << px << ' ' << py << '\n';
	al_draw_text(font,
		al_map_rgb(255, 255, 255),width/2,py,ALLEGRO_ALIGN_CENTER,
		msg.c_str());

}
void setAntialias() {
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

}
void TextButton::generate(string msg, imgGroup img , pair<float,float> pos,int centered) {


	float width = al_get_bitmap_width(getSysgame()->getAllegroHandler()->getImg(img.img_a));
	float height = al_get_bitmap_height(getSysgame()->getAllegroHandler()->getImg(img.img_a));

	width = int(width);
	height = int(height);

	//setAntialias();
	
	//setAntialias();
	
	//setAntialias();

	
	ALLEGRO_BITMAP *a = al_create_bitmap(width, height);
	al_set_target_bitmap(a);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_a),0,0,0);//al_create_bitmap(width,height);
	blitCentered(getViewer()->getFont("roboto_v1"), msg, al_map_rgb(255, 255, 255),a);
	ALLEGRO_BITMAP *b = al_create_bitmap(width, height);
	al_set_target_bitmap(b);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_b),0,0,0);
	blitCentered(getViewer()->getFont("roboto_v1"), msg, al_map_rgb(255, 255, 255),b);

	ALLEGRO_BITMAP *c = al_create_bitmap(width, height);
	al_set_target_bitmap(c);
	al_draw_bitmap(getSysgame()->getAllegroHandler()->getImg(img.img_c),0,0,0);
	blitCentered(getViewer()->getFont("roboto_v1"), msg, al_map_rgb(255, 255, 255),c);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));

	
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


TextButton::~TextButton() {
	
}
