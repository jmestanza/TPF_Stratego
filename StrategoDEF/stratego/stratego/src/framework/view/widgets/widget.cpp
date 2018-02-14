#include "widget.h"

#include <framework\sysgame\sysgame.h>
#include <chrono>
#include <random>
using namespace std;

//mt19937 g1 ( chrono::system_clock::now().time_since_epoch().count() );

Widget::Widget(Sysgame *sys,string _name) : mySysgame(sys) , name(_name){
	view = sys->getAllegroHandler();
	_beingDrawn = 0;
}
void Widget::killMe() {
	_killMe = 1;
}
pair <float,float> Widget::getPos() {
	return pos;
}
void Widget::setPosSize(pair<int,int> _pos,pair <int,int> _size,bool centered) {
	pos = _pos;
	size = _size;
	if (centered) {
		pos.first -= size.first / 2;
		pos.second -= size.second / 2;
	}
}
bool Widget::insideMe(int x,int y){
	return x >= pos.first && x <= pos.first + size.first && y >= pos.second && y <= pos.second + size.second;
}
void Widget::setPos(pair<int,int> _pos,bool centered) {
	setPosSize(_pos,size,centered);
}
bool Widget::getKillMe() {
	return _killMe;
}
void Widget::hide() {
	callStopDrawing();
}
void Widget::show() {
	callStartDrawing();
}
void Widget::callStartDrawing() {
	if (!_beingDrawn) {
		startDrawing();
		_beingDrawn = 1;
	}
}
void Widget::callStopDrawing() {
	if (_beingDrawn) {
		stopDrawing();
		_beingDrawn = 0;
	}
}
pair <float,float> Widget::getSize() {
	return size;
}
Sysgame* Widget::getSysgame() {
	return mySysgame;
}
Viewer* Widget::getViewer() {
	return view;
}
string Widget::getName() {
	return name;
}

Widget::~Widget() {}
