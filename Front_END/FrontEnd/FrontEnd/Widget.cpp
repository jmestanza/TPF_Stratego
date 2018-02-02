#include "Widget.h"
#include <chrono>
#include <random>
using namespace std;

mt19937 g1 ( chrono::system_clock::now().time_since_epoch().count() );

Widget::Widget(Viewer *_view) {
	view = _view;
	id = g1();
}


Widget::~Widget() {}
