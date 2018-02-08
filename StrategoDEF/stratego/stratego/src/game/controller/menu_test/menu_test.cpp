#include "menu_test.h"
#include <cmath>

#include <framework\view\widgets\text_button.h>
using namespace std;

imgGroup g_blue() {
	return imgGroup("button_blue_a","button_blue_b","button_grey");
}
imgGroup g_green() {
	return imgGroup("button_green_a","button_green_b","button_grey");
}
menuTest::menuTest(Sysgame *_sys) : Controller(_sys){
	value = 2;
	Background* background = new Background(mySysgame,
		"background1", tuple<uc, uc, uc>(0,200,255),
		pair<float, float>(0,0), 
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);
	//Table * tablero = new Table(mySysgame,"table", "test_blue","test_red",pair<float, float>(200.0, 200.0), pair<float, float>(56, 76));
	pair<float,float> size = view->getScreenSize();
	float width = size.first , height = size.second;
	
	textButton *myButton = new textButton(mySysgame,"button_1");
	myButton->generate("PRESS",g_blue(),pair<float,float>(width/2,height*3/4),1);

	myButton->onClick([](Sysgame *sys) {
		((menuTest*)sys->getController())->value ++;
		textButton *myButtonB = new textButton(sys,"button_"+to_string(  ((menuTest*)sys->getController())->value ));

		pair<float,float> size = sys->getAllegroHandler()->getScreenSize();
		int width = size.first,height = size.second;

		mt19937 g1(std::chrono::system_clock::now().time_since_epoch().count());
		float px = abs(int(g1())) % width;
		float py = abs(int(g1())) % height;
		myButtonB->generate("WOWOWOW! ",g_green(),pair<float,float>(px,py),1);
		myButtonB->onClick([](Sysgame *sys) {
			cout << "hello world \n";
		});

		sys->getUI()->AddWidget( (Widget*)myButtonB);

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
