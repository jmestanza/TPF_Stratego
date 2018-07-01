#include "connect_menu.h"

/*
Este es el controlador del menu de conectar.
Aqui se programa como es la interaccion del usuario cuando esta intentando conectarse 
tanto como cliente (buscando el servidor), como servidor (esperando un cliente)
*/


#include <framework\view\widgets\widget.h>
#include <framework\view\widgets\background.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\Animation.h>
#include <framework\view\widgets\showClocks\showTime.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\view\widgets\checkbox\checkbox.h>

#include <framework\utils\random_number.h>
#include <game\controller\connectionLostMenu\connectionLostMenu.h>
#include <game\controller\menu_test\menu_test.h>
#include <game\controller\gameArea\gameArea.h>

ConnectMenu::ConnectMenu(Sysgame *sys) : Controller(sys){
	_startedToConnect = 0;
	InfoMessageAdded = 0;
	InfoIconAdded = 0;
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
	input->setText("127.0.0.1");
	
	pair<int,int> posBox(input->getPos().first+10,input->getPos().second+input->getSize().second+10);
	Checkbox *box = new Checkbox(mySysgame,"checkbox");
	box->configure("icon_check_box0","icon_check_box1",posBox,0);
	box->onTick([](Sysgame *sys,int status) {
		if (!status) {
			((TextInput*)sys->getUI()->getWidget("input"))->enable();
		} else {
			((TextInput*)sys->getUI()->getWidget("input"))->disable();
		}
	});
	int bx = posBox.first , by = posBox.second;
	screenText *textCheckBox = new screenText(mySysgame,"text_checkbox");
	textCheckBox->configure("Esperar cliente","roboto_small",view->getColor("black"));
	textCheckBox->setPos( pair<int,int>( bx + box->getSize().first + 10 , by + 10 ) , 0);

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
	addWidget((Widget*)box);
	addWidget((Widget*)textCheckBox);

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
	//Animation *animation = new Animation(mySysgame,"connecting_animation");
	/*vector <string> data;
	getLoadingAImgs(data);
	animation->configure(data);
	addWidget((Widget*)animation);*/

	/*screenText *text = new screenText(mySysgame,"text_connecting");
	text->configure(
		"Intentando conectar como cliente","roboto_v30",view->getColor("black"));
	addWidget((Widget*)text);*/

	addInfoAnim();
	addInfoMessage("Intentando conectar como cliente","black");

	addCancelButtonCenter();
		
		/*new TextButton(mySysgame,"button_cancel");
	buttonCancel->generate(
		"CANCELAR",g_red(),pair<float,float>(screenSize.first/2,screenSize.second*7/8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");*/

	//connectContent.push_back("text_connecting");
	//connectContent.push_back("connecting_animation");
	//connectContent.push_back("button_cancel");

	//setInfoObjects((Widget*)text,(Widget*)animation);

	/*callIn(1000, [](Sysgame *sys) {
	
		ConnectMenu *myself = (ConnectMenu*)sys->getController();
		if (!sys->getNetwork()->getConnected()) {
			sys->getNetwork()->closeConnection();
			myself->setConnectionFailed();
		}
	});*/
}
void ConnectMenu::createConnectButton() {
	

	pair<float,float> screenSize = view->getScreenSize();
	connectButton = new TextButton(mySysgame,"connect_button");
	connectButton->generate(
		"CONECTAR",g_connectButton(),
		pair<float,float>(screenSize.first / 4 * 3,screenSize.second / 2),1);
	connectButton->onClick([](Sysgame *sys) {
		((TextButton*)sys->getUI()->getWidget("connect_button"))->disable();
		ConnectMenu* connectMenu = (ConnectMenu*)(sys->getController());
		if (((Checkbox*)sys->getUI()->getWidget("checkbox"))->getStatus()) {
			connectMenu->waitForConnection();
			connectMenu->eraseWidget("checkbox");
		} else {
			if (!connectMenu->startedToConnect()) connectMenu->startToConnect();
		}
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
	//// Borrar icono y mensaje
	removeInfoMessage();
	removeInfoThing();


	status = "trying_to_connect_2";
	
	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	int waitTime = randrange(3000,5000);

	ConnectMenu* connectMenu = (ConnectMenu*)mySysgame->getController();

	
	addCancelButtonCenter();
	
	addInfoMessage("Reintentando en ","black");
	screenText *waitTextA = (screenText*)getWidget("text_msg");
	int pos_x = this->infoPositionA.first + waitTextA->getSize().first/2 + 20;
	int pos_y = this->infoPositionA.second - waitTextA->getSize().second/2 + 2;

	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v30","black",pair<float,float>(pos_x,pos_y),0);
	showTime->setTarget(waitTime);
	showTime->showMillis();

	int iconPosX = pos_x + showTime->getSize().first + 250;

	addInfoIcon("icon_warning");

	addWidget((Widget*)showTime);

	showTime->onTime([](Sysgame *sys) {
		ConnectMenu* connectMenu = (ConnectMenu*)sys->getController();

		connectMenu->eraseWidget("show_time");

		cout << "on time \n";
		pair<float,float> screenSize = sys->getAllegroHandler()->getScreenSize();

		
		connectMenu->setStatus("trying_to_connect_3");
		sys->getNetwork()->tryConnection(connectMenu->getConnectIP(),stoi(sys->getConfigurationData()["port"]),1000);
		
		connectMenu->removeInfoMessage();
		connectMenu->removeInfoThing();
		
		connectMenu->addInfoMessage("Intentando conectar como cliente","black");
		connectMenu->addInfoAnim();

		
	});


}
pair<float,float> ConnectMenu::getInfoPositionA() {
	return infoPositionA;
}
void ConnectMenu::setStatus(string _status) {
	status = _status;
}
string ConnectMenu::getStatus() {
	return status;
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

	
	removeCancelButton();
	removeInfoMessage();
	removeInfoThing();

	TextButton *buttonCancel = new TextButton(mySysgame,"button_again");
	buttonCancel->generate(
		"INTENTAR DENUEVO",g_red(),pair<float,float>(screenSize.first / 4,screenSize.second * 7 / 8),1);
	addWidget((Widget*)buttonCancel);
	buttonCancel->addIcon("icon_left");
	TextButton *buttonWait = new TextButton(mySysgame,"button_wait");
	buttonWait->generate(
		"ESPERAR CONEXION",g_connectButtonLong(),pair<float,float>(screenSize.first * 3 / 4,screenSize.second * 7 / 8),1);
	buttonWait->addIcon("icon_networking");
	connectContent.push_back("button_wait");

	buttonCancel->onClick([](Sysgame *sys) {
		ConnectMenu * connectMenu = (ConnectMenu*)sys->getController();
		
		connectMenu->eraseWidget("button_again");
		connectMenu->eraseWidget("button_wait");
		connectMenu->removeInfoMessage();
		connectMenu->removeInfoThing();

		connectMenu->setNotConnecting();

 		TextButton* connectButton = (TextButton*)sys->getUI()->getWidget("connect_button");
		connectButton->enable();

	});

	buttonWait->onClick([](Sysgame *sys) {
		ConnectMenu * connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->eraseWidget("button_again");
		connectMenu->eraseWidget("button_wait");

		connectMenu->waitForConnection();
	});

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
	removeInfoMessage();
	removeInfoThing();

	mySysgame->getNetwork()->waitForConnection(stoi(mySysgame->getConfigurationData()["port"]));

	pair<float,float> screenSize = mySysgame->getAllegroHandler()->getScreenSize();

	addCancelButtonCenter();
	addInfoMessage("Esperando un cliente","black");
	addInfoAnim();
}
void ConnectMenu::setConnectionSuccess() {

	this->eraseWidget("input");
	this->eraseWidget("connect_button");
	this->generateNameInput();

	addInfoMessage("Conexion establecida","black");
	addInfoIcon("icon_success");

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
	addInfoMessage("Esperando nombre del oponente","black");
	addInfoAnim();

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

	addInfoMessage("Realizando sorteo","black");
	addInfoAnim();

	pair <float,float> screenSize = view->getScreenSize();
	pair <float,float> outScreen = pair<float,float>(screenSize.first+10,screenSize.second+10);

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

	addInfoMessage(msg,"black");
	addInfoIcon("icon_info");

	callIn(2000,[](Sysgame *sys) {
		ConnectMenu* connectMenu = (ConnectMenu*)sys->getController();
		connectMenu->goToGame();
	});

}
void ConnectMenu::goToGame() {
	mySysgame->setNewController((Controller*)new gameArea(mySysgame,getName(),getOpponentName(),localStart,this->mode));
}

void ConnectMenu::addInfoMessage(string msg,string color) {
	if (InfoMessageAdded) removeInfoMessage();

	screenText *text = new screenText(mySysgame,"text_msg");
	text->configure(
		msg,"roboto_v30",view->getColor(color));
	text->setPos(infoPositionA,1);
	addWidget((Widget*)text);
	InfoMessageAdded = 1;
}
void ConnectMenu::removeInfoMessage() {
	if (!InfoMessageAdded) return;

	eraseWidget("text_msg");
	InfoMessageAdded = 0;
}
void ConnectMenu::addInfoIcon(string icon) {
	if (InfoIconAdded) removeInfoThing();

	Background *background = new Background(mySysgame,"info_icon");
	background->configureImg(icon);
	background->setPos(infoPositionB,1);
	addWidget((Widget*)background);

	InfoIconAdded = 1;
}
void ConnectMenu::addInfoAnim() {
	if (InfoIconAdded) removeInfoThing();

	Animation *animation = new Animation(mySysgame,"info_icon");
	vector <string> data;
	getLoadingAImgs(data);
	animation->configure(data);
	((Widget*)animation)->setPos(infoPositionB,1);
	addWidget((Widget*)animation);

	InfoIconAdded = 1;
}

void ConnectMenu::removeInfoThing() {
	if (!InfoIconAdded) return;
	eraseWidget("info_icon");
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
	if (cancelButtonAdded) {
		removeCancelButton();
	}
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
	cancelButtonAdded = 1;

	return buttonCancel;
}
void ConnectMenu::removeCancelButton() {
	if (!cancelButtonAdded) return;

	eraseWidget("button_cancel");

	cancelButtonAdded = 0;
}
ConnectMenu::~ConnectMenu(){

}
