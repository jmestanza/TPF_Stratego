#pragma once
#include <allegro5\allegro.h>
#include <framework\sysgame\sysgame.h>
#include <framework\view\allegro_manager\allegro_manager.h>
#include <random>
#include <chrono>
#include "naive_button.h"
using namespace std;

class imgGroup {
	public:
		imgGroup(string _a,string _b,string _c);
		string img_a,img_b,img_c;
};

class TextButton : public NaiveButton {
	private:
		int n1,n2,n3;
	public:
		TextButton(Sysgame* sys, string name);
		void generate(string msg,imgGroup img,pair<float,float> pos,int centered);
		virtual ~TextButton();
};

