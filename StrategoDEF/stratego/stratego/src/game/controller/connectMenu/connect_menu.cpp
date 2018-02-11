#include "connect_menu.h"

/****
Este es el controlador del menu de conectar.
Aqui se programa como es la interaccion del usuario cuando esta intentando conectarse 
tanto como cliente (buscando el servidor), como servidor (esperando un cliente)
-****/


#include <framework\view\widgets\widget.h>
#include <framework\view\widgets\background.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\Animation.h>
#include <framework\view\widgets\showClocks\showTime.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\utils\random_number.h>

#include <game\controller\menu_test\menu_test.h>

ConnectMenu::ConnectMenu(Sysgame *sys) : Controller(sys){
	_startedToConnect = 0;
	
}
void ConnectMenu::onCreate() {
	pair<float, float> screenSize = view->getScreenSize();
	infoPositionA = pair<float,float>(screenSize.first/8*3,screenSize.second / 16 * 11 + 5);
	infoPositionB = pair<float,float>(screenSize.first*3/4,screenSize.second / 16 * 11 + 5);

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
		//waitTime = randrange(3000,5000);
		connectIP = input->getText();
		mySysgame->getNetwork()->tryConnection(connectIP,stoi(mySysgame->getConfigurationData()["port"]), 1000 );
		
		status = "trying_to_connect";
	} catch (NetworkManagerException &e) {
		cout << "error: " << e.what() << '\n';
		setConnectionFailed();
		status = "connection_failed";
		return ; /// nothing more to do
	}

	connectButton->disable();
	_startedToConnect = 1;
	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();
	Animation *animation = new Animation(mySysgame,"connecting_animation");
	vector <string> data;
	getLoadingAImgs(data);
	animation->configure(data);
	addWidget((Widget*)animation);

	screenText *text = new screenText(mySysgame,"text_connecting");
	text->configure(
		"Intentando conectar como cliente","roboto_v30",view->getColor("black"));
	addWidget((Widget*)text);

	TextButton *buttonCancel = new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first/2,screenSize.second*7/8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");

	connectContent.push_back("text_connecting");
	connectContent.push_back("connecting_animation");
	connectContent.push_back("button_cancel");

	setInfoObjects((Widget*)text,(Widget*)animation);
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
		//cout << "status = " << status << '\n';
		if (status == "trying_to_connect") {
			setConnectionWaitTimeout();
		} else if (status == "trying_to_connect_2") {
			setConnectionFailed();
		}
		
	}
}
void ConnectMenu::setConnectionWaitTimeout() {
	status = "trying_to_connect_2";
	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	int waitTime = randrange(3000,5000);

	ConnectMenu* connectMenu = (ConnectMenu*)mySysgame->getController();

	eraseWidget("text_connecting");

	TextButton *buttonCancel = new TextButton(mySysgame,"button_cancel_b");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first / 2,screenSize.second * 7 / 8),1);
	
	buttonCancel->addIcon("icon_left");
	connectContent.push_back("button_cancel_b");

	int pos_x = screenSize.first * 3 / 8;
	int pos_y = screenSize.second * 3 /4;
	screenText *waitTextA = new screenText(mySysgame,"wait_text_a");
	waitTextA->configure("Reintentando en ","roboto_v30",view->getColor("black"));
	
	connectContent.push_back("wait_text_a");
	
	pos_x += waitTextA->getSize().first/2 + 15;
	pos_y -= waitTextA->getSize().second/2 - 2;
	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v30","black",pair<float,float>(pos_x,pos_y),0);
	showTime->setTarget(waitTime);
	showTime->showMillis();

	connectContent.push_back("show_time");

	mySysgame->getUI()->getWidget("connecting_animation")->hide();

	int iconPosX = pos_x + showTime->getSize().first + 250;
	Background *iconError = new Background(mySysgame,"icon_error_b");
	iconError->configureImg("icon_warning");
	connectContent.push_back("icon_error_b");

	setInfoObjects((Widget*)waitTextA,(Widget*)iconError);

	addWidget((Widget*)buttonCancel);
	addWidget((Widget*)waitTextA);
	addWidget((Widget*)showTime);
	addWidget((Widget*)iconError);

	showTime->onTime([](Sysgame *sys) {
		pair<float,float> screenSize = sys->getAllegroHandler()->getScreenSize();

		ConnectMenu* connectMenu = (ConnectMenu*)sys->getController();
		sys->getNetwork()->tryConnection(connectMenu->getConnectIP(),stoi(sys->getConfigurationData()["port"]),1000);
		connectMenu->eraseWidget("show_time");
		connectMenu->eraseWidget("wait_text_a");
		connectMenu->eraseWidget("icon_error_b");

		screenText *text = new screenText(sys,"connect_text_2");
		text->configure("Intentando conectar como cliente","roboto_v30",sys->getAllegroHandler()->getColor("black")
			,pair<float,float>(screenSize.first * 3 / 8,screenSize.second * 3 / 4),1);
		sys->getUI()->getWidget("connecting_animation")->show();
		connectMenu->addWidget((Widget*)text);
		connectMenu->getConnectContent().push_back("connect_text_2");

		
	});


}
vector<string>& ConnectMenu::getConnectContent() {
	return connectContent;
}
string ConnectMenu::getConnectIP() {
	return connectIP;
}
void ConnectMenu::setConnectionFailed() {
	status = "connection_failed";

	if (connectButton->enabled()) connectButton->disable();

	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	
	ConnectMenu* connectMenu = (ConnectMenu*)mySysgame->getController();
	connectMenu->eraseConnectContent();

	screenText *text = new screenText(mySysgame,"text_failure");
	text->configure(
		"Fallo en el intento de conexion","roboto_v30",view->getColor("red"));
	
	connectContent.push_back("text_failure");

	Background *background = new Background(mySysgame,"icon_error");
	background->configureImg("icon_cancel");
	connectContent.push_back("icon_error");

	setInfoObjects((Widget*)text,(Widget*)background);

	TextButton *buttonCancel = new TextButton(mySysgame,"button_again");
	buttonCancel->generate(
		"INTENTAR DENUEVO",g_red(),pair<float,float>(screenSize.first / 4,screenSize.second * 7 / 8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");
	connectContent.push_back("button_again");

	TextButton *buttonWait = new TextButton(mySysgame,"button_wait");
	buttonWait->generate(
		"ESPERAR CONEXION",g_connectButtonLong(),pair<float,float>(screenSize.first * 3 / 4,screenSize.second * 7 / 8),1);
	buttonWait->addIcon("icon_networking");
	connectContent.push_back("button_wait");

	buttonCancel->onClick([](Sysgame *sys) {
		ConnectMenu * connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->setNotConnecting();
		connectMenu->eraseConnectContent();


 		TextButton* connectButton = (TextButton*)sys->getUI()->getWidget("connect_button");
		connectButton->enable();

	});

	buttonWait->onClick([](Sysgame *sys) {
		ConnectMenu * connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->eraseConnectContent();

		sys->getNetwork()->waitForConnection( stoi(sys->getConfigurationData()["port"]) );
	
		pair<float,float> screenSize = sys->getAllegroHandler()->getScreenSize();

		TextButton *buttonCancel = new TextButton(sys,"button_cancel");
		buttonCancel->generate(
			"CANCELAR",g_red(),pair<float,float>(screenSize.first / 2,screenSize.second * 7 / 8),1);
		sys->getController()->addWidget((Widget*)buttonCancel);
		buttonCancel->addIcon("icon_left");

		
	});

	addWidget((Widget*)text);
	addWidget((Widget*)background);
	addWidget((Widget*)buttonCancel);
	addWidget((Widget*)buttonWait);
}
void ConnectMenu::setInfoObjects(Widget *aw,Widget *bw) {
	aw->setPos(infoPositionA,1);
	bw->setPos(infoPositionB,1);
	infoObjectA = aw;
	infoObjectB = bw;
}
void ConnectMenu::eraseInfoObjects() {

}
void ConnectMenu::eraseConnectContent() {
	//cout << "called\n";
	for (int i = 0;i < connectContent.size();i++) {
		if (mySysgame->getUI()->getWidget(connectContent[i]) != nullptr) {
			mySysgame->getUI()->RemoveWidget(connectContent[i]);
		}
	}
	connectContent.clear();
}
void ConnectMenu::setNotConnecting() {
	_startedToConnect = 0;
}
ConnectMenu::~ConnectMenu(){

}
