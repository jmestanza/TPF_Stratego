#include "gameArea.h"

#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\utils\good_buttons.h>
#include <game\controller\menu_test\menu_test.h>
#include <game\controller\connectionLostMenu\connectionLostMenu.h>

gameArea::gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart) : Controller(sys) {
	name = _name;
	opponentName = _opponentName;
	localStart = _localStart;
}
void gameArea::onCreate() {
	addBackgroundImg("background1");

	pair<float,float> screenSize = view->getScreenSize();

	pair <float,float> textArea(screenSize.first/2,screenSize.second*7/8);

	screenText *gameAreaText = new screenText(mySysgame,"title");
	gameAreaText->configure("AREA DE JUEGO","Fredoka_small",view->getColor("black"),textArea,1);

	TextButton *button = new TextButton(mySysgame,"return_button_b");
	button->generate(
		"VOLVER",g_blue(),
		pair<float,float>(screenSize.first - 170,screenSize.second / 16),1
	);
	button->addIcon("icon_left");

	button->onClick([](Sysgame *sys) {
		sys->getNetwork()->closeConnection();
		sys->setNewController(new MenuTest(sys));
	});
	addWidget((Widget*)button);
}
void gameArea::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void gameArea::onNetEvent(NETWORK_EVENT *ev) {
	if (ev->msg == "connlost") {
		mySysgame->setNewController(new connectionLostMenu(mySysgame));
	}
}


gameArea::~gameArea() {}
