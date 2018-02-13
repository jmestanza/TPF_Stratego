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
#include <game\controller\connectionLostMenu\connectionLostMenu.h>
#include <game\controller\menu_test\menu_test.h>
#include <game\controller\gameArea\gameArea.h>

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
	input->setText("192.168.86.75");
	

	TextButton *button = new TextButton(mySysgame,"return_button");
	button->generate(
		"VOLVER", g_blue(), 
		pair<float, float>(screenSize.first - 170, screenSize.second / 16 ),1
	);
	button->addIcon("icon_left");

	button->onClick([](Sysgame *sys) {
		sys->getNetwork()->closeConnection();
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

	addCancelButtonCenter();
		
		/*new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first/2,screenSize.second*7/8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");*/

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
	cout << "new package: "<<package << '\n';
	if (status == "waiting_for_name_request" && package == "name") {
		/// dos casos
		cout << "we recived name when we where waiting for name \n";
		if (hasName()) { /// A: Ya se ingreso por el input el nombre
			sendName(getName());
			status = "waiting_for_ack";
			cout<< "waiting for ack\n";
		} else { /// Todavia no se ingreso por el input el nombre
			status = "wait_for_name_input";
			cout << "waiting for name input\n";
		}
	} else if (status == "waiting_for_name_content" && package == "name_is") {
		cout << "we recived name content when we where waiting for name content\n";
		setOpponentName(data["nombre"]);
		if (mode == "server") {
			/// ahora hacemos el sorteo
			sendAck();
			status = "waiting_for_name_request";
			cout << "waiting for name request \n";
		} else if (mode == "client") {
			sendAck();
			status = "waiting_for_draw";
			cout << "waiting for draw \n";
		} else {
			cout << "Error incorrect mode!\n";
		}
	} else if (status == "waiting_for_ack" && package == "ack") {
		cout << "we recived ack when we where waiting for ack\n";
		if (mode == "server") {
			status = "make_draw";
			makeDraw();
			cout << "making draw\n";
		} else if (mode == "client") {
			sendNameRequest();
			status = "waiting_for_name_content";
			cout << "waiting for name data\n";
		} else {
			cout << "Error incorrect mode (2)!";
		}
	} else if (status == "waiting_for_draw") {
		if (package == "you_start") {
			cout << "you start! \n";
			readyToStart(1);
		} else if (package == "i_start") {
			cout << "I start! \n";
			readyToStart(0);
		}
	}
	
}

void ConnectMenu::onNetEvent(NETWORK_EVENT *ev) {
	if (ev->msg == "connfailed") {
		//cout << "status = " << status << '\n';
		if (status == "trying_to_connect") {
			setConnectionWaitTimeout();
		} else if (status == "trying_to_connect_3") {
			setConnectionFailed();
		}
		
	} else if (ev->msg == "connected") {
		if (status == "trying_to_connect" || status == "trying_to_connect_3") {
			mode = "client";
		} else if (status == "wait_for_connection"){
			mode = "server";
		} else {
			cout << "Error: unexpected situation";
		}
		nameInputFilled = 0;
		setConnectionSuccess();

		if (this->mode == "server") {
			/// ask for initial data
			cout << "I am server \n";
			sendNameRequest();
			status = "waiting_for_name_content";
		} else if (this->mode == "client") {
			cout << "I am client \n";
			status = "waiting_for_name_request";
		}
	} else if (ev->msg == "connlost") {
		mySysgame->setNewController(new connectionLostMenu(mySysgame));
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

	
	screenText *waitTextA = new screenText(mySysgame,"wait_text_a");
	waitTextA->configure("Reintentando en ","roboto_v30",view->getColor("black"));
	
	connectContent.push_back("wait_text_a");
	
	int pos_x = this->infoPositionA.first + waitTextA->getSize().first/2 + 20;
	int pos_y = this->infoPositionA.second - waitTextA->getSize().second/2 + 2;

	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v30","black",pair<float,float>(pos_x,pos_y),0);
	//cout << waitTime << '\n';
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
		connectMenu->setStatus("trying_to_connect_3");
		sys->getNetwork()->tryConnection(connectMenu->getConnectIP(),stoi(sys->getConfigurationData()["port"]),1000);
		connectMenu->eraseWidget("show_time");
		connectMenu->eraseWidget("wait_text_a");
		connectMenu->eraseWidget("icon_error_b");

		screenText *text = new screenText(sys,"connect_text_2");
		text->configure("Intentando conectar como cliente","roboto_v30",sys->getAllegroHandler()->getColor("black"));
		text->setPos(connectMenu->getInfoPositionA(),1);

		sys->getUI()->getWidget("connecting_animation")->show();
		connectMenu->addWidget((Widget*)text);
		connectMenu->getConnectContent().push_back("connect_text_2");
	
		
	});


}
pair<float,float> ConnectMenu::getInfoPositionA() {
	return infoPositionA;
}
void ConnectMenu::setStatus(string _status) {
	status = _status;
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
		connectMenu->waitForConnection();
	});

	addWidget((Widget*)text);
	addWidget((Widget*)background);
	addWidget((Widget*)buttonCancel);
	addWidget((Widget*)buttonWait);
}

Animation* ConnectMenu::generateAnimationWidget(string name) {
	Animation *animation = new Animation(mySysgame,name);
	vector <string> data;
	getLoadingAImgs(data);
	animation->configure(data);
	return animation;
}
screenText* ConnectMenu::generateScreenText(string msg,string font,string name) {
	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();
	screenText *text = new screenText(mySysgame,name);
	text->configure(
		msg,font,view->getColor("black"),pair<float,float>(screenSize.first / 2,screenSize.second / 4),1);
	return text;
}
void ConnectMenu::waitForConnection() {
	this->setStatus("wait_for_connection");
	mySysgame->getNetwork()->waitForConnection(stoi(mySysgame->getConfigurationData()["port"]));

	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	TextButton *buttonCancel = new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first / 2,screenSize.second * 7 / 8),1);
	mySysgame->getController()->addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");
	buttonCancel->onClick([](Sysgame *sys){
		sys->getNetwork()->closeConnection();
		sys->setNewController(new ConnectMenu(sys));
	});


	Animation *anim = generateAnimationWidget("connecting_animation");
	screenText *text = generateScreenText("Esperando un cliente","roboto_v30","waiting_for_client_msg");
	setInfoObjects((Widget*)text,(Widget*)anim);
	addWidget((Widget*)anim);
	addWidget((Widget*)text);

	connectContent.push_back("button_cancel");
	connectContent.push_back("connecting_animation");
	connectContent.push_back("waiting_for_client_msg");
}
void ConnectMenu::setConnectionSuccess() {
	this->eraseConnectContent();

	screenText *text = new screenText(mySysgame,"success_text");
	text->configure("Conexion establecida","roboto_v30",view->getColor("green"));
	Background* background = new Background(mySysgame,"ok_icon");
	background->configureImg("icon_success");
	setInfoObjects(text,background);

	this->eraseWidget("input");
	this->eraseWidget("connect_button");

	addWidget((Widget*)text);
	addWidget((Widget*)background);
	this->generateNameInput();

	connectContent.push_back("success_text");
	connectContent.push_back("ok_icon");
}
void ConnectMenu::generateNameInput() {
	pair<float,float> screenSize = view->getScreenSize();
	input = new TextInput(mySysgame,"input_name");
	input->configure(pair<float,float>(screenSize.first / 8 * 3,screenSize.second / 2),1);
	input->addIcon("icon_user");
	input->addSmallText("Nombre");
	input->setText("ariel");

	connectButton = new TextButton(mySysgame,"play_button");
	connectButton->generate(
		"COMENZAR",g_connectButton(),
		pair<float,float>(screenSize.first / 4 * 3,screenSize.second / 2),1);
	connectButton->onClick([](Sysgame *sys) {
		ConnectMenu *connectMenu = (ConnectMenu*)sys->getController();
		TextInput* nameInput = (TextInput*)sys->getUI()->getWidget("input_name");
		string name = nameInput->getText();
		if (name != "") {
			TextButton* connectButton = (TextButton*)sys->getUI()->getWidget("play_button");
			connectButton->disable();
			/// dos casos
			connectMenu->setPlayerName(name);

		}
	});
	addWidget((Widget*)input);
	addWidget((Widget*)connectButton);
	
}

void ConnectMenu::setPlayerName(string name) {
	eraseConnectContent();

	setName(name);
	Animation *anim = generateAnimationWidget("connecting_animation");
	screenText *text = generateScreenText("Esperando nombre del oponente","roboto_v30","waiting_for_client_name");
	setInfoObjects((Widget*)text,(Widget*)anim);
	addWidget((Widget*)anim);
	addWidget((Widget*)text);

	connectContent.push_back("connecting_animation");
	connectContent.push_back("waiting_for_client_name");

	if (status == "wait_for_name_input") {
		sendName(name);
		cout << "sending name, waiting for ack\n";
		status = "waiting_for_ack";
	} else {
		cout << "name set, waiting for request\n";
	}
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

void ConnectMenu::setName(string name) {
	myName = name;
	gotName = 1;
}
void ConnectMenu::setOpponentName(string name) {
	opponentName = name;
	gotOpponentName = 1;
}
int ConnectMenu::hasName() {
	return gotName;
}
int ConnectMenu::hasOpponentName() {
	return gotOpponentName;
}
string ConnectMenu::getName() {
	return myName;
}
string ConnectMenu::getOpponentName() {
	return opponentName;
}

void ConnectMenu::sendName(string name) {
	map <string,string> data;
	data["nombre"] = name;
	data["count"] = name.size();
	mySysgame->getNetwork()->sendPackage("name_is",data);
}
void ConnectMenu::sendAck() {
	map <string,string> data;
	mySysgame->getNetwork()->sendPackage("ack",data);
}
void ConnectMenu::makeDraw() {
	this->eraseConnectContent();

	Animation *anim = generateAnimationWidget("connecting_animation_b");
	screenText *text = generateScreenText("Realizando sorteo","roboto_v30","draw_message");
	setInfoObjects((Widget*)text,(Widget*)anim);
	addWidget((Widget*)anim);
	addWidget((Widget*)text); 

	connectContent.push_back("connecting_animation_b");
	connectContent.push_back("draw_message");

	pair <float,float> screenSize = view->getScreenSize();
	pair <float,float> outScreen = pair<float,float>(screenSize.first+10,screenSize.second+10);

	

	connectContent.push_back("clock_draw");
	callIn(1000,[](Sysgame *sys) {
		int randomValue = randrange(0,2);
		ConnectMenu *connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->readyToStart(randomValue);

		map <string,string> data;
		if (randomValue == 1) {
			sys->getNetwork()->sendPackage("i_start",data);
		} else if (randomValue == 0) {
			sys->getNetwork()->sendPackage("you_start",data);
		} else {
			cout << "Unexpected situation (randomValue wrong)\n";
		}
	});

	 addCancelButtonCenter();
	
}
void ConnectMenu::sendNameRequest() {
	map <string,string> data;
	mySysgame->getNetwork()->sendPackage("name",data);
}
void ConnectMenu::readyToStart(int _localStart) {
	localStart = _localStart;
	eraseConnectContent();

	string msg;
	if (localStart == 1) {
		msg = "Empezas vos";
	} else {
		msg = "Empieza tu rival";
	}
	pair <float,float> screenSize = view->getScreenSize();

	Background *icon = new Background(mySysgame,"info_icon");
	icon->configureImg("icon_info");
	screenText *text = generateScreenText(msg,"roboto_v30","draw_result");
	setInfoObjects((Widget*)text,(Widget*)icon);
	addWidget((Widget*)icon);
	addWidget((Widget*)text);

	connectContent.push_back("info_icon");
	connectContent.push_back("draw_result");

	TextButton *buttonStartGame = new TextButton(mySysgame,"start_game_button");
	pair<float,float> buttonPos(screenSize.first/2,screenSize.second*7/8);
	buttonStartGame->generate("COLOCAR PIEZAS",g_connectButtonLong(),buttonPos,1);
	buttonStartGame->addIcon("icon_token");
	connectContent.push_back("start_game_button");

	addWidget( (Widget*)buttonStartGame);

	buttonStartGame->onClick([](Sysgame *sys) {
		ConnectMenu* connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->goToGame();
	});

	/*pair <float,float> outScreen = pair<float,float>(screenSize.first + 10,screenSize.second + 10);
	ShowTime *showTime = new ShowTime(mySysgame,"clock_draw");
	showTime->configure("roboto_v30","black",outScreen,0);

	showTime->setTarget(1000);
	showTime->configure("roboto_v30","black",outScreen,0);*/
}
void ConnectMenu::goToGame() {
	mySysgame->setNewController((Controller*)new gameArea(mySysgame,getName(),getOpponentName(),localStart));
}
TextButton* ConnectMenu::addCancelButtonCenter() {
	pair<float,float> screenSize = view->getScreenSize();
	return addCancelButton(pair<int,int>(screenSize.first/2,screenSize.second*7/8));
}
TextButton* ConnectMenu::addCancelButtonLeft() {
	pair<float,float> screenSize = view->getScreenSize();
	return addCancelButton(pair<int,int>(screenSize.first/4,screenSize.second*7/8));
}
TextButton* ConnectMenu::addCancelButton(pair <int,int> posInt) {
	pair<float,float>pos = pair<float,float>(posInt.first,posInt.second);

	TextButton *buttonCancel = new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pos,1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");
	buttonCancel->onClick([](Sysgame *sys) {
		sys->getNetwork()->closeConnection();
		sys->setNewController(new ConnectMenu(sys));
	});
	connectContent.push_back("button_cancel");
	return buttonCancel;
}

ConnectMenu::~ConnectMenu(){

}
