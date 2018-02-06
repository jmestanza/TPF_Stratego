#include "widget.h"

#include <framework\sysgame\sysgame.h>
#include <chrono>
#include <random>
using namespace std;

//mt19937 g1 ( chrono::system_clock::now().time_since_epoch().count() );

Widget::Widget(Sysgame *sys,string _name) : mySysgame(sys) , name(_name){
	view = sys->getAllegroHandler();
}
string Widget::getName() {
	return name;
}

Widget::~Widget() {}
