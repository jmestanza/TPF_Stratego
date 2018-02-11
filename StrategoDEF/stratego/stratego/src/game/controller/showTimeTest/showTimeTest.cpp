#include "showTimeTest.h"

#include <framework\view\widgets\background.h>
#include <framework\view\widgets\showClocks\showTime.h>


showTimeTest::showTimeTest(Sysgame *sys) : Controller(sys) {}

void showTimeTest::onCreate() {
	Background* back = new Background(mySysgame,"background");
	back->configure("light_blue",pair<float,float>(0,0),view->getScreenSize(),0);

	float screenWidth = view->getScreenSize().first, screenHeight = view->getScreenSize().second;
	pair<float,float> screenHalf = pair<float,float>(screenWidth/2,screenHeight);
	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v1","black",screenHalf,1);

	addWidget((Widget*)back);
}
void showTimeTest::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void showTimeTest::onNetEvent(NETWORK_EVENT *ev) {

}

showTimeTest::~showTimeTest() {}
