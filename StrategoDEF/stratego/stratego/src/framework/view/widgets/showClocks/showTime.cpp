#include "showTime.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>
#include <framework\utils\random_number.h>
#include <framework\utils\getMillisFromEpoch.h>
#include <framework\view\utils\copyBitmap.h>
#include <algorithm>
using namespace std;

ShowTime::ShowTime(Sysgame *sys,string name) : Widget(sys,name) {
	myCode = "show_timer_"+to_string(randomNumber());
	_showMinutes = 0;
	_showMiliSeconds = 0;
	_zeroComplete = 1;
	onTimeFunction = nullptr;
}

void ShowTime::configure(string font,string color,pair<float,float> _pos,int centered) {
	ALLEGRO_FONT* currentFont = view->getFont(font);
	ALLEGRO_COLOR currentColor = view->getColor(color);

	pair <int,int> _size = pair<int,int>(0,0);
	int max_width = 0;
	for (int i = 0;i < 10;i++) { /// Generate numbers
		int bbx,bby,bbw,bbh;
		al_get_text_dimensions(currentFont,to_string(i).c_str(),&bbx,&bby,&bbw,&bbh);
		
		_size.second = max(_size.second,bbh);
		max_width = max(max_width , bbw);
	}
	for (int i = 0;i < 10;i++) addCharData(to_string(i),max_width,_size.second,currentFont,currentColor);
	addCharData(":",max_width,_size.second,currentFont,currentColor);
	addCharData(" ",max_width,_size.second,currentFont,currentColor);
	_baseWidth = max_width;
	_size.second = _baseWidth *2;
	if (_showMiliSeconds) {
		_size.first += _baseWidth *3;
	} else if (_showMinutes) {
		_size.first += _baseWidth *3;
	}
	this->setPosSize(_pos,_size,centered);
	al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
}
void ShowTime::onTime(void(*func)(Sysgame*)) {
	onTimeFunction = func;
}
void ShowTime::showMillis() {
	_showMiliSeconds = 1;
}
void ShowTime::showMinutes() {
	_showMinutes = 1;
}
void ShowTime::addCharData(string val,int width,int height,ALLEGRO_FONT* font,ALLEGRO_COLOR color) {
	ALLEGRO_BITMAP* aux = al_create_bitmap(width,height);
	al_set_target_bitmap(aux);
	int bbx,bby,bbw,bbh;
	al_get_text_dimensions(font,val.c_str(),&bbx,&bby,&bbw,&bbh);
	int px = width / 2 - bbw / 2 - bbx; 
	int py = height / 2 - bbh / 2 - bby;
	al_draw_text(font,color,px,py,0,val.c_str());
	string code = myCode + "_" + val;
	view->loadFromBitmap(aux,code);
	letterCodes[val] = code;
}
void ShowTime::setTarget(int miliseconds) {
	targetTime = getMillisFromEpoch() + miliseconds;
}
void ShowTime::handleEvent(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_TIMER) {
		int min,sec,mil; computeTimeLeft(min,sec,mil);
		string sMin = getStr(min),sSec = getStr(sec),sMil = getStr(mil);


		if (_showMinutes) {
			view->changeShowImg(myCode + "_m0",letterCodes[string(1,sMin[0])]);
			view->changeShowImg(myCode + "_m1",letterCodes[string(1,sMin[1])]);
		}

		view->changeShowImg(myCode + "_s0",letterCodes[string(1,sSec[0])]);
		view->changeShowImg(myCode + "_s1",letterCodes[string(1,sSec[1])]);

		if (_showMiliSeconds) {
			view->changeShowImg(myCode + "_mm0",letterCodes[string(1,sMil[0])]);
			//view->changeShowImg(myCode + "_mm1",letterCodes[string(1,sMil[1])]);
		}
		if (timeDone()) {
			if (onTimeFunction) onTimeFunction(mySysgame);
		}
	}
}
int ShowTime::timeDone() {
	//cout << targetTime - getMillisFromEpoch() << 
	;
	return (long long)(targetTime - getMillisFromEpoch()) <= 0;
}
void ShowTime::startDrawing() {
	//cout << "Start to draw \n";
	/// show seconds
	int pos_x = this->pos.first;
	int pos_y = this->pos.second;
	int min,sec,mil; computeTimeLeft(min,sec,mil);
	string sMin = getStr(min) ,sSec = getStr(sec) , sMil= getStr(mil);
	
	if (_showMinutes) {
		view->show(letterCodes[string(1,sMin[0])],myCode + "_m0",pos_x,pos_y); pos_x += _baseWidth;
		view->show(letterCodes[string(1,sMin[1])],myCode + "_m1",pos_x,pos_y); pos_x += _baseWidth;
		view->show(letterCodes[":"],myCode + ":a",pos_x,pos_y); pos_x += _baseWidth;
		currentlyShowing.push_back(myCode + ":a");
		currentlyShowing.push_back(myCode + "_m0");
		currentlyShowing.push_back(myCode + "_m1");
	}

	/// show seconds
	view->show(letterCodes[string(1,sSec[0])],myCode + "_s0",pos_x,pos_y); pos_x += _baseWidth;
	view->show(letterCodes[string(1,sSec[1])],myCode + "_s1",pos_x,pos_y); pos_x += _baseWidth;
	currentlyShowing.push_back(myCode + "_s0");
	currentlyShowing.push_back(myCode + "_s1");

	if (_showMiliSeconds) {
		view->show(letterCodes[":"],myCode + ":b",pos_x,pos_y); pos_x += _baseWidth;
		view->show(letterCodes[string(1,sMil[0])],myCode+"_mm0",pos_x,pos_y); pos_x += _baseWidth;
		//view->show(letterCodes[string(1,sMil[1])],myCode+"_mm1",pos_x,pos_y); pos_x += _baseWidth;
		
		currentlyShowing.push_back(myCode + ":b");
		currentlyShowing.push_back(myCode + "_mm0");
		//currentlyShowing.push_back(myCode + "_mm1");
	}
}
void ShowTime::computeTimeLeft(int &min,int &sec,int &mil) {
	long long timeLeft = max(0LL, (long long)(targetTime - getMillisFromEpoch()) );
	sec = timeLeft / 1000 % 60;
	mil = timeLeft / 10 % 100;
	min = timeLeft / 1000 / 60 % 60;
	//cout << sec << '\n';
}
string ShowTime::getStr(int val) {
	string add = "";
	if (val < 10) add += _zeroComplete ? "0" : " ";
	
	return add + to_string(val);
}
void ShowTime::stopDrawing() {
	for (int i = 0;i < currentlyShowing.size();i++) view->stopShow(currentlyShowing[i]);
	currentlyShowing.clear();
}

ShowTime::~ShowTime() {}
