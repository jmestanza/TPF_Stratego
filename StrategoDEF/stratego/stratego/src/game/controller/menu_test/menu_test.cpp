#include "menu_test.h"

#include <framework\view\widgets\text_button.h>

imgGroup g_blue() {
	return imgGroup("button_blue_a","button_blue_b","button_grey");
}
menuTest::menuTest(Sysgame *_sys) : Controller(_sys){
	
	Background* background = new Background(mySysgame,
		"background1", tuple<uc, uc, uc>(255,255,255),
		pair<float, float>(0,0), 
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);
	//Table * tablero = new Table(mySysgame,"table", "test_blue","test_red",pair<float, float>(200.0, 200.0), pair<float, float>(56, 76));
	pair<float,float> size = view->getScreenSize();
	float width = size.first , height = size.second;

	textButton *myButton = new textButton(mySysgame,"button_1");
	myButton->generate("PRESS",g_blue(),pair<float,float>(width/2,height*3/4));
	myButton->onClick([](Sysgame *sys) {

		sys->getUI()->RemoveWidget("button_1");

	});

	mySysgame->getUI()->AddWidget( (Widget*) background );
	//mySysgame->getUI()->AddWidget( (Widget*) tablero );
	mySysgame->getUI()->AddWidget( (Widget*) myButton);
}

void menuTest::onNetPack(string &package, map<string, string> &data) {
	// handle NETWORK actions
}
void menuTest::onNetEvent(NETWORK_EVENT *ev) {

}


menuTest::~menuTest(){
	
}
