#include "showTimeTest.h"

#include <framework\view\widgets\background.h>
#include <framework\view\widgets\showClocks\showTime.h>
#include <framework\view\widgets\Table.h>
#include <framework\view\widgets\widget.h>

showTimeTest::showTimeTest(Sysgame *sys) : Controller(sys) {}

void showTimeTest::onCreate() {
	addBackgroundImg("background1");


	pair <float,float> screenSize = view->getScreenSize();

	Table* tablero = new Table(mySysgame,"table","test_blue","test_red",pair<float,float>(60,60),1);
	tablero->setPos(pair<float,float>(20 + tablero->getSize().first / 2,screenSize.second / 2),1);
	tablero->setPlayersName("ARIEL","JOAQUIN");


	addWidget((Widget*)tablero);
	/*Background* back = new Background(mySysgame,"background");
	back->configure("light_blue",pair<float,float>(0,0),view->getScreenSize(),0);

	float screenWidth = view->getScreenSize().first, screenHeight = view->getScreenSize().second;
	pair<float,float> screenHalf = pair<float,float>(screenWidth/2,screenHeight/2);
	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v30","black",screenHalf,1);
	showTime->setTarget(70000);
	showTime->showMillis();
	showTime->showMinutes();

	addWidget((Widget*)back);
	addWidget((Widget*)showTime);*/


	//Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float> _screen_center,pair<float,float>_pieceSize);


}
void showTimeTest::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void showTimeTest::onNetEvent(NETWORK_EVENT *ev) {

}

showTimeTest::~showTimeTest() {}
