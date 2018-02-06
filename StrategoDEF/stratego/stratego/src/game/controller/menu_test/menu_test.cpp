#include "menu_test.h"



menuTest::menuTest(Sysgame *_sys) : Controller(_sys){
	Background* background = new Background(mySysgame,
		"background1", tuple<uc, uc, uc>(255,255,255),
		pair<float, float>(0,0), 
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);

	mySysgame->getUI()->AddWidget( (Widget*)background );
}

void menuTest::onNetPack(string &package, map<string, string> &data) {
	// handle NETWORK actions
}
void menuTest::onNetEvent(NETWORK_EVENT *ev) {

}


menuTest::~menuTest()
{
}
