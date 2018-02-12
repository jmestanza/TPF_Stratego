#include "connectionLostMenu.h"

#include <framework\view\widgets\background.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\utils\good_buttons.h>
#include <game\controller\menu_test\menu_test.h>

connectionLostMenu::connectionLostMenu(Sysgame *sys) : Controller(sys) {}

void connectionLostMenu::onCreate() {
	pair <float,float> screenSize = view->getScreenSize();

	Background* background2 = new Background(mySysgame,"background2");
	background2->configureImg(
		"background1",
		pair<float,float>(screenSize.first / 2,screenSize.second / 2),
		1);

	addWidget((Widget*)background2);

	pair<float,float> textPos(screenSize.first/2,screenSize.second/4);
	screenText *text = new screenText(mySysgame,"title_error");
	text->configure("CONEXION PERDIDA","Fredoka_small",view->getColor("black"),textPos,1);
	addWidget((Widget*)text);

	pair<float,float> buttonPos(screenSize.first/2,screenSize.second/4*3);

	TextButton *returnButton = new TextButton(mySysgame,"return_button");
	returnButton->generate("IR AL INICIO",g_red(),buttonPos,1);
	returnButton->addIcon("icon_left");

	addWidget((Widget*)returnButton);


	returnButton->onClick([](Sysgame *sys) {
		sys->setNewController(new MenuTest(sys));
	});
}
void connectionLostMenu::onNetPack(string &package,map<string,string> &data) {
}// handle NETWORK actions
void connectionLostMenu::onNetEvent(NETWORK_EVENT *ev) {

}

connectionLostMenu::~connectionLostMenu() {}
