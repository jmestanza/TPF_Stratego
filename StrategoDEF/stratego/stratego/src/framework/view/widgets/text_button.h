#pragma once
#include <framework\sysgame\sysgame.h>
#include "naive_button.h"

struct imgGroup {
	imgGroup(string _a,string _b,string _c);
	string img_a,img_b,img_c;
};

class textButton : public NaiveButton {
	public:
		textButton(Sysgame* sys, string name);
		void generate(string msg, imgGroup img);
		virtual ~textButton();
};

