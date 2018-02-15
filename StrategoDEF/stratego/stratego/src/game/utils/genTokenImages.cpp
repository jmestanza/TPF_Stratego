#include "genTokenImages.h"

string let = "0123456789BFS";

void gen(Viewer *view, string type) {
	for (int i = 0;i < let.size();i++) {
		string codeToken = "token_" + string(1,let[i]) + type;
		if (!view->hasLoadedImg(codeToken+"_r")) {
			ALLEGRO_BITMAP* token = view->getImg(codeToken);
			int token_width = al_get_bitmap_width(token), token_height = al_get_bitmap_height(token);
			ALLEGRO_BITMAP* finalToken = al_create_bitmap(60,60);
			al_set_target_bitmap(finalToken);
			int sx = 0,sy = 0,sw = token_width , sh = token_height , dx = 1 , dy = 1, dw = 59, dh = 59, flags = 0;
			al_draw_scaled_bitmap(token,
				sx,sy,sw,sh,
				dx,dy,dw,dh,flags);
			view->loadFromBitmap(finalToken,codeToken+"_r");
		}
	}
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
}

void genTokenImages(Viewer* view) {
	gen(view,"B");
	gen(view,"R");
}