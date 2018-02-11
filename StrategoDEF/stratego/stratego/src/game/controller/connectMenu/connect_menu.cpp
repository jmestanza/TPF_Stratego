#include "connect_menu.h"

#include <framework\view\widgets\widget.h>
#include <framework\view\widgets\background.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\Animation.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\utils\random_number.h>

#include <game\controller\menu_test\menu_test.h>

ConnectMenu::ConnectMenu(Sysgame *sys) : Controller(sys){
	_startedToConnect = 0;
}
void ConnectMenu::onCreate() {
	pair<float, float> screenSize = view->getScreenSize();

	pair<float,float> size = view->getScreenSize();
	float width = size.first,height = size.second;

	Background *background = new Background(mySysgame,"background");
	background->configureImg(
		"background1",
		pair<float,float>(width / 2,height / 2),
		1);

	screenText *text = new screenText(mySysgame, "text_connect");
	text->configure(
		"JUEGO EN RED", "Fredoka_small", view->getColor("black"), pair<float, float>(screenSize.first/2, screenSize.second/4), 1);
	
	input = new TextInput(mySysgame, "input");
	input->configure(pair<float, float>(screenSize.first / 8 * 3, screenSize.second / 2),1);
	input->addIcon("icon_worldwide");
	input->addSmallText("Direccion IP");

	

	TextButton *button = new TextButton(mySysgame,"return_button");
	button->generate(
		"VOLVER", g_blue(), 
		pair<float, float>(screenSize.first - 170, screenSize.second / 16 ),1
	);
	button->addIcon("icon_left");

	button->onClick([](Sysgame *sys) {
		sys->setNewController(new MenuTest(sys));
	});
	

	addWidget((Widget*)background);
	addWidget((Widget*)text);
	addWidget((Widget*)input);
	addWidget((Widget*)button);

	createConnectButton();
	
}
void ConnectMenu::startToConnect() {
	//// Now real actions
	try {
		waitTime = randrange(3000,5000);
		mySysgame->getNetwork()->tryConnection(input->getText(),stoi(mySysgame->getConfigurationData()["port"]), waitTime );
	} catch (NetworkManagerException &e) {
		cout << "error: " << e.what() << '\n';
		setConnectionFailed();
		return ; /// nothing more to do
	}

	connectButton->disable();
	_startedToConnect = 1;
	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();
	Animation *animation = new Animation(mySysgame,"connecting_animation");
	vector <string> data;
	getLoadingAImgs(data);
	animation->configure(
		data,pair<float,float>(screenSize.first * 3 / 4,screenSize.second * 3 / 4),1);
	addWidget((Widget*)animation);

	screenText *text = new screenText(mySysgame,"text_connecting");
	text->configure(
		"Intentando conectar como cliente","roboto_v30",view->getColor("black"),
		pair<float,float>(screenSize.first/8*3,screenSize.second*3/4),1);
	addWidget((Widget*)text);

	TextButton *buttonCancel = new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first/2,screenSize.second*7/8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");
}
void ConnectMenu::createConnectButton() {

	pair<float,float> screenSize = view->getScreenSize();
	connectButton = new TextButton(mySysgame,"connect_button");
	connectButton->generate(
		"CONECTAR",g_connectButton(),
		pair<float,float>(screenSize.first / 4 * 3,screenSize.second / 2),1);
	connectButton->onClick([](Sysgame *sys) {
		ConnectMenu* connectMenu = (ConnectMenu*)(sys->getController());

		if (!connectMenu->startedToConnect()) connectMenu->startToConnect();
	});

	addWidget((Widget*)connectButton);
}
int ConnectMenu::startedToConnect() {
	return _startedToConnect;
}
void ConnectMenu::onNetPack(string &package, map<string, string> &data) {

}
void ConnectMenu::onNetEvent(NETWORK_EVENT *ev) {
	if (ev->msg == "connfailed") {
		setConnectionFailed();
		
	}
}
void ConnectMenu::setConnectionFailed() {

	if (connectButton->enabled()) connectButton->disable();

	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	
	mySysgame->getUI()->RemoveWidget("text_connecting");
	mySysgame->getUI()->RemoveWidget("connecting_animation");
	mySysgame->getUI()->RemoveWidget("button_cancel");
	

	screenText *text = new screenText(mySysgame,"text_failure");
	text->configure(
		"Fallo en el intento de conexion","roboto_v30",view->getColor("red"),
		pair<float,float>(screenSize.first /2 ,screenSize.second / 4 *3  ),1);
	

	int iconPosX = screenSize.first / 2 +text->getSize().first/2 + 50;

	Background *background = new Background(mySysgame,"icon_error");
	background->configureImg(
		"icon_cancel",pair<float,float>(iconPosX, screenSize.second/4*3 + 5),1);

	TextButton *buttonCancel = new TextButton(mySysgame,"button_again");
	buttonCancel->generate(
		"INTENTAR DENUEVO",g_red(),pair<float,float>(screenSize.first / 4,screenSize.second * 7 / 8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");

	buttonCancel->onClick([](Sysgame *sys) {
 		TextButton* connectButton = (TextButton*)sys->getUI()->getWidget("connect_button");
		connectButton->enable();

		sys->getUI()->RemoveWidget("icon_error");
		sys->getUI()->RemoveWidget("text_failure");
		sys->getUI()->RemoveWidget("button_again");
		sys->getUI()->RemoveWidget("button_wait");

		ConnectMenu * connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->setNotConnecting();
	});

	TextButton *buttonWait = new TextButton(mySysgame,"button_wait");
	buttonWait->generate(
		"ESPERAR CONEXION",g_connectButtonLong(),pair<float,float>(screenSize.first*3/4,screenSize.second * 7/8),1);
	buttonWait->addIcon("icon_networking");

	buttonWait->onClick([](Sysgame *sys) {
		sys->getNetwork()->waitForConnection( stoi(sys->getConfigurationData()["port"]) );
	});

	addWidget((Widget*)text);
	addWidget((Widget*)background);
	addWidget((Widget*)buttonCancel);
	addWidget((Widget*)buttonWait);
}
void ConnectMenu::setNotConnecting() {
	_startedToConnect = 0;
}
ConnectMenu::~ConnectMenu(){

}
