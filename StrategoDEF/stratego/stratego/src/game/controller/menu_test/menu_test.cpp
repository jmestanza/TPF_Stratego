#include "menu_test.h"



menuTest::menuTest(Sysgame *_sys) : Controller(_sys){
	Background* background = new Background(mySysgame,
		"background1", tuple<uc, uc, uc>(255,255,255),
		pair<float, float>(0,0), 
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);
	Table * tablero = new Table(mySysgame,"table", "test_blue","test_red",pair<float, float>(200.0, 200.0), pair<float, float>(56, 76));


	mySysgame->getUI()->AddWidget( (Widget*) background );
	mySysgame->getUI()->AddWidget( (Widget*) tablero );

}

void menuTest::onNetPack(string &package, map<string, string> &data) {
	// handle NETWORK actions
}
void menuTest::onNetEvent(NETWORK_EVENT *ev) {

}


menuTest::~menuTest()
{
}
