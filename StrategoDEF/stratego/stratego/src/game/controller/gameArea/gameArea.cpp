#include "gameArea.h"

#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\view\widgets\TokenContainer\TokenContainer.h>
#include <framework\view\widgets\TokenContainer\MouseFollower.h>
#include <game\controller\menu_test\menu_test.h>
#include <game\controller\connectionLostMenu\connectionLostMenu.h>

gameArea::gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart) : Controller(sys) {
	name = _name;
	opponentName = _opponentName;
	localStart = _localStart;
	status = "select_token";

	
}
void gameArea::onCreate() {
	addBackgroundImg("background1");
	selectedItem = "";

	pair<float,float> screenSize = view->getScreenSize();

	//screenText *gameAreaText = new screenText(mySysgame,"title");
	//gameAreaText->configure("AREA DE JUEGO","Fredoka_small",view->getColor("black"),textArea,1);

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

	/**** TABLERO Y PIEZAS *******/

	Table* tablero = new Table(mySysgame,"table","test_blue","test_red",pair<float,float>(60,60),1);
	tablero->setPos(pair<float,float>(20 + tablero->getSize().first / 2,screenSize.second / 2),1);
	tablero->setPlayersName(name,opponentName);

	addWidget((Widget*)tablero);

	/*** CONTENEDOR DE PIEZAS ***/
	TokenContainer *cont = new TokenContainer(mySysgame,"token_container");
	int halfPoint = (tablero->getPos().first + tablero->getSize().first + screenSize.first) / 2;
	pair <float,float> posToken(halfPoint - cont->getSize().first / 2,screenSize.second - cont->getSize().second - 70);

	cont->configure(posToken);

	addWidget((Widget*)cont);

	/*** MOUSE FOLLOWER ***/
	MouseFollower *follow = new MouseFollower(mySysgame,"mouse_selected");
	addWidget((Widget*)follow);

	/*** AREA DE MENSAJES ***/

	pair <float,float> infoPosition((20 + tablero->getSize().first + screenSize.first)/2,screenSize.second/2) ;
	pair <float,float> iconPosition(screenSize.first - 40,screenSize.second / 2);

	screenText *msg = new screenText(mySysgame,"info_msg");
	Background *icon = new Background(mySysgame,"background");

	//pair <float,float>

	msg->configure("Coloca las fichas","roboto_v1",view->getColor("black"),infoPosition,1);

	addWidget((Widget*)msg);

	/**** ACCIONES CONJUNTAS DEL TABLERO Y EL CONTENEDOR DE PIEZAS ***/

	cont->onTokenSelect([](Sysgame *sys,string selected) {
		gameArea* myself = (gameArea*)sys->getController();
		myself->setSelectedItem(selected);

		MouseFollower *follow = (MouseFollower*)sys->getUI()->getWidget("mouse_selected");
		follow->setImg("token_" + selected + "_r");

		Table *board = (Table*)sys->getUI()->getWidget("table");
		board->informSelected(selected);
	});

	tablero->onMouseRelease([](Sysgame *sys,Table *table,pair<int,int> pos) {
		TokenContainer *tk = (TokenContainer*)sys->getUI()->getWidget("token_container");

		gameArea *controller = (gameArea*)sys->getController();

		if (controller->getSelectedItem() != "") {
			if (table->getPiece(pos) != "empty") {
				tk->incContent(table->getPiece(pos));

			}
			table->putToken(controller->getSelectedItem(),pos);
			tk->removeContent(controller->getSelectedItem());
			controller->setSelectedItem("");
		}
	});

	tablero->onMousePress([](Sysgame *sys,Table *table,pair<int,int> pos) {
		TokenContainer *tk = (TokenContainer*)sys->getUI()->getWidget("token_container");
		gameArea *controller = (gameArea*)sys->getController();

		if (table->getPiece(pos) != "empty") {
			tk->incContent(table->getPiece(pos));
			MouseFollower *follow = (MouseFollower*)sys->getUI()->getWidget("mouse_selected");
			follow->setImg("token_" + table->getPiece(pos) + "_r");

			controller->setSelectedItem(table->getPiece(pos));

			table->freePosition(pos);
		}
	});

}
string gameArea::getSelectedItem() {
	return selectedItem;
}
void gameArea::setSelectedItem(string value) {
	 selectedItem = value;
}
void gameArea::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void gameArea::onNetEvent(NETWORK_EVENT *ev) {
	if (ev->msg == "connlost") {
		mySysgame->setNewController(new connectionLostMenu(mySysgame));
	}
}


gameArea::~gameArea() {}
