#include "menu_test.h"
#include <cmath>

#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\utils\good_buttons.h>
#include <game\controller\aboutWindow\aboutWindow.h>
#include <game\controller\connectMenu\connect_menu.h>

using namespace std;



MenuTest::MenuTest(Sysgame *_sys) : Controller(_sys) {}
void MenuTest::onCreate(){
	pair<float,float> size = view->getScreenSize();
	float width = size.first,height = size.second;

	value = 2;
	Background* background = new Background(mySysgame,"background1");
	background->configureImg(
		"background1",
		pair<float, float>(width/2,height/2),
		1);

	//Table * tablero = new Table(mySysgame,"table", "test_blue","test_red",pair<float, float>(200.0, 200.0), pair<float, float>(56, 76));
	
	TextButton *myButton = new TextButton(mySysgame,"button_1");
	myButton->generate("JUGAR",g_blue(),pair<float,float>(width/4,height*3/4),1);
	myButton->addIcon("icon_play");
	TextButton *myButton2 = new TextButton(mySysgame,"button_2");
	myButton2->generate("ACERCA DE",g_blue(),pair<float,float>(width / 4 * 3,height * 3 / 4),1);

	screenText *gameTitle = new screenText(mySysgame,"game_title");
	gameTitle->configure("STRATEGO","Fredoka",al_map_rgb(0,0,0),pair<float,float>(width/2,height/4),1);

	myButton->onClick([](Sysgame *sys) {
		//sys->getAllegroHandler()->playonce("sonic");
		sys->setNewController((Controller*)new ConnectMenu(sys));
	});
	myButton2->onClick([](Sysgame *sys) {
		sys->setNewController((Controller*)new AboutWindow(sys));
	});

	mySysgame->getUI()->AddWidget( (Widget*) background );
	mySysgame->getUI()->AddWidget( (Widget*) myButton);
	mySysgame->getUI()->AddWidget( (Widget*) myButton2 );
	mySysgame->getUI()->AddWidget( (Widget*) gameTitle );

}

void MenuTest::onNetPack(string &package, map<string, string> &data) {
	// handle NETWORK actions
}
void MenuTest::onNetEvent(NETWORK_EVENT *ev) {

}


MenuTest::~MenuTest(){
	
}
