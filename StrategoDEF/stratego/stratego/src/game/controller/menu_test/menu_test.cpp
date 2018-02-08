#include "menu_test.h"
#include <cmath>

#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\utils\good_buttons.h>
#include <game\controller\aboutWindow\aboutWindow.h>

using namespace std;



menuTest::menuTest(Sysgame *_sys) : Controller(_sys) {}
void menuTest::onCreate(){
	value = 2;
	Background* background = new Background(mySysgame,"background1");
	background->configure(
		al_map_rgb(109,189,214),
		pair<float, float>(0,0), 
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);
	//Table * tablero = new Table(mySysgame,"table", "test_blue","test_red",pair<float, float>(200.0, 200.0), pair<float, float>(56, 76));
	pair<float,float> size = view->getScreenSize();
	float width = size.first , height = size.second;
	
	textButton *myButton = new textButton(mySysgame,"button_1");
	myButton->generate("JUGAR",g_blue(),pair<float,float>(width/4,height*3/4),1);

	textButton *myButton2 = new textButton(mySysgame,"button_2");
	myButton2->generate("ACERCA DE",g_blue(),pair<float,float>(width / 4 * 3,height * 3 / 4),1);

	screenText *gameTitle = new screenText(mySysgame,"game_title");
	gameTitle->configure("STRATEGO","Fredoka",al_map_rgb(0,0,0),pair<float,float>(width/2,height/4),1);

	myButton->onClick([](Sysgame *sys) {
		sys->getAllegroHandler()->playonce("sonic");
	});
	myButton2->onClick([](Sysgame *sys) {
		sys->setNewController((Controller*)new AboutWindow(sys));
	});

	mySysgame->getUI()->AddWidget( (Widget*) background );
	mySysgame->getUI()->AddWidget( (Widget*) myButton);
	mySysgame->getUI()->AddWidget( (Widget*) myButton2 );
	mySysgame->getUI()->AddWidget( (Widget*) gameTitle );

}

void menuTest::onNetPack(string &package, map<string, string> &data) {
	// handle NETWORK actions
}
void menuTest::onNetEvent(NETWORK_EVENT *ev) {

}


menuTest::~menuTest(){
	
}
