#include "connect_menu.h"

#include <framework\view\widgets\background.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\utils\good_buttons.h>
#include <game\controller\menu_test\menu_test.h>

ConnectMenu::ConnectMenu(Sysgame *sys) : Controller(sys){
	
}
void ConnectMenu::onCreate() {
	pair<float, float> screenSize = view->getScreenSize();
	Background *background = new Background(mySysgame,"background");
	background->configure("light_blue",
		pair<float, float>(0, 0),
		screenSize,0);

	

	screenText *text = new screenText(mySysgame, "text_connect");
	text->configure(
		"Juego en red", "Akrobat", view->getColor("black"), pair<float, float>(10, 10), 0);
	
	TextInput *input = new TextInput(mySysgame, "input");
	input->configure(pair<float, float>(screenSize.first / 8 * 3, screenSize.second / 2),1);
	input->addIcon("icon_worldwide");

	TextButton *connectButton = new TextButton(mySysgame, "connect_button");
	connectButton->generate(
		"CONNECTAR", g_connectButton(),
		pair<float, float>(screenSize.first / 4 * 3, screenSize.second / 2), 1);

	TextButton *button = new TextButton(mySysgame,"return_button");
	button->generate(
		"VOLVER", g_blue(), 
		pair<float, float>(screenSize.first - 170, screenSize.second / 16 ),1
	);

	button->onClick([](Sysgame *sys) {
		sys->setNewController(new MenuTest(sys));
	});

	addWidget((Widget*)background);
	addWidget((Widget*)text);
	addWidget((Widget*)input);
	addWidget((Widget*)button);
	addWidget((Widget*)connectButton);
}
void ConnectMenu::onNetPack(string &package, map<string, string> &data) {

}
void ConnectMenu::onNetEvent(NETWORK_EVENT *ev) {

}

ConnectMenu::~ConnectMenu(){

}
