#pragma once
#include <allegro5\allegro.h>
#include <framework\view\widgets\naive_button.h>

struct buttonImages {
	buttonImages(string _a,string _b,string _b);
	string img_a,img_b,img_c;
};
NaiveButton *generateButton(string text, string img);