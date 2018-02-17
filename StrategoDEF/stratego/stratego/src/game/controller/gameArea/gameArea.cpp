#include "gameArea.h"

#include <string>
#include <game\model\stratego_engine\Player.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\view\widgets\TokenContainer\TokenContainer.h>
#include <framework\view\widgets\TokenContainer\MouseFollower.h>
#include <framework\view\widgets\Animation.h>

#include <game\controller\menu_test\menu_test.h>
#include <game\controller\connectionLostMenu\connectionLostMenu.h>

using namespace std;

gameArea::gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart,string _mode) : Controller(sys) {

	gameEngine = new Player(_localStart ? RED : BLUE);
	

	name = _name;
	opponentName = _opponentName;
	localStart = _localStart;
	status = "select_token";
	mode = _mode;

	tokensToPlace = 40;
	startButtonPresent = 0;
	optionButtonPresent = 0;
	animationAdded = 0;
	hasOk = 0;


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

	Table* tablero = new Table(mySysgame,"table","test_blue","test_red",pair<float,float>(60,60),localStart);
	tablero->setPos(pair<float,float>(20 + tablero->getSize().first / 2,screenSize.second / 2),1);
	tablero->setPlayersName(opponentName,name);

	addWidget((Widget*)tablero);

	/*** CONTENEDOR DE PIEZAS ***/
	TokenContainer *cont = new TokenContainer(mySysgame,"token_container");
	halfPoint = (tablero->getPos().first + tablero->getSize().first + screenSize.first) / 2;
	quarterPoint = (screenSize.first - (tablero->getPos().first + tablero->getSize().first)) / 4 + tablero->getPos().first + tablero->getSize().first;
	threeQuartersPoint = (screenSize.first - (tablero->getPos().first + tablero->getSize().first)) / 4 * 3 + tablero->getPos().first + tablero->getSize().first;
	pair <float,float> posToken(halfPoint - cont->getSize().first / 2,screenSize.second - cont->getSize().second - 70);

	cont->configure(posToken);

	addWidget((Widget*)cont);

	/*** MOUSE FOLLOWER ***/
	MouseFollower *follow = new MouseFollower(mySysgame,"mouse_selected");
	addWidget((Widget*)follow);

	/*** AREA DE MENSAJES ***/

	pair <float,float> infoPosition(cont->getPos().first+10,cont->getPos().second-20) ;
	pair <float,float> iconPosition(screenSize.first - 40,screenSize.second / 2);

	screenText *msg = new screenText(mySysgame,"info_msg");
	Background *icon = new Background(mySysgame,"background");

	//pair <float,float>

	msg->configure("Faltan 40 fichas","roboto_small",view->getColor("black"),infoPosition,0);

	addWidget((Widget*)msg);

	addOptionsButtons();

	if (localStart) {
		cont->addAllRedContent();
	} else {
		cont->addAllBlueContent();
	}




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
		if (pos.first <= 5) return;
		TokenContainer *tk = (TokenContainer*)sys->getUI()->getWidget("token_container");

		gameArea *controller = (gameArea*)sys->getController();

		if (controller->getSelectedItem() != "") {
			int delta = 0;
			//cout << table->getPiece(pos) << '\n';
			if (table->getPiece(pos) != "empty") {
				tk->incContent(table->getPiece(pos));
				delta ++;
			}
			table->putToken(controller->getSelectedItem(),pos);
			tk->removeContent(controller->getSelectedItem());
			controller->setSelectedItem("");
			delta --;
			//cout << "Delta = " << delta << '\n';
			if (delta == -1) controller->decTokens();
			
		}
	});

	tablero->onMousePress([](Sysgame *sys,Table *table,pair<int,int> pos) {
		if (pos.first <= 5) return;
		TokenContainer *tk = (TokenContainer*)sys->getUI()->getWidget("token_container");
		gameArea *controller = (gameArea*)sys->getController();

		if (table->getPiece(pos) != "empty") {
			tk->incContent(table->getPiece(pos));
			controller->incTokens();
			MouseFollower *follow = (MouseFollower*)sys->getUI()->getWidget("mouse_selected");
			follow->setImg("token_" + table->getPiece(pos) + "_r");

			controller->setSelectedItem(table->getPiece(pos));

			table->freePosition(pos);
		}
	});

}
void gameArea::decTokens() {
	tokensToPlace --;
	updateTokenMsg();
}
void gameArea::incTokens() {
	tokensToPlace ++;
	updateTokenMsg();
}
void gameArea::addStartButton() {
	if (startButtonPresent) return;

	pair<float,float> screenSize = view->getScreenSize();

	TextButton *startButton = new TextButton(mySysgame,"start_button");
	startButton->generate("COMENZAR",g_connectButtonLong(),pair<float,float>(halfPoint,screenSize.second - 40),1);
	startButton->addIcon("icon_success_small");
	startButton->onClick([](Sysgame *sys) {
		gameArea *myself = (gameArea*)sys->getController();
		myself->tokenReady();
	});

	addWidget((Widget*)startButton);
	startButtonPresent = 1;
}
void gameArea::tokenReady() {
	((TokenContainer*)getWidget("token_container"))->onTokenSelect(nullptr);

	removeStartButton();
	removeOptionsButtons();

	Table* table = (Table*)getWidget("table");

	table->fillOpponentField(localStart ? "B" : "R");
	table->setStatus("locked");
	table->onMousePress(nullptr);
	table->onMouseRelease(nullptr);

	//// Add enemy token container 

	pair<int,int> screenSize = view->getScreenSize();

	TokenContainer *cont = new TokenContainer(mySysgame,"token_container_enemy");
	pair <float,float> posToken(halfPoint - cont->getSize().first / 2, 90);
	cont->configure(posToken);

	addWidget((Widget*)cont);



	if (this->mode == "server") {
		
		cout << "coloacmos las fichas, somos servidor \n";

		map <string,string> data;
		mySysgame->getNetwork()->sendPackage("r_u_ready",data);
		
		cout << "Enviamos el r_u_ready \n";

		if (localStart) {
			this->status = "waiting_for_ok";
			cout << "Esepramos el ok \n";
		} else {
			this->status = "waiting_for_opp_move";
			cout << "esperamos el primer movimiento del rival\n";
		}
		removeWaitingMsg();
		addWaitingMsg("Esperando al oponente");
		addAnimation();

	} else if (this->mode == "client") {
		cout << "colocamos las fichas, somos cliente \n";

		if (this->status == "r_u_ready_recv") {
			if (localStart) {
				this->status = "waiting_for_move";
				removeWaitingMsg();
				addWaitingMsg("Es tu turno");
				cout << "ya recibimos el r_u_ready, y empezamos nosotros, \n";
				cout << "status = " << this->status << '\n';
			} else {
				this->status = "waiting_for_opp_move";
				map<string,string> data;
				mySysgame->getNetwork()->sendPackage("i_am_ready",data);
				removeWaitingMsg();
				addWaitingMsg("Esperando al oponente");
				addAnimation();
				cout << "ya recibimos el r_u_ready, empeiza el rival, le mandamos el i_am_ready y esperamos su primer movimiento \n";
				cout << "status = " << this->status << '\n';

			}
		} else if (this->status == "select_token") {
			cout << "No recibimos el r_u_ready, esperamos a que el rival lo envie \n";
			this->status = "waiting_r_u_ready";

			cout << "status = " << this->status << '\n';
			removeWaitingMsg();
			addWaitingMsg("Esperando al oponente");
			addAnimation();
		}
	}

	loadEngineContent(table->getContent());

	//// Acciones de juego
	table->onActionMove([](Sysgame *sys,Table* tbl,pair<int,int> org_src,pair<int,int> org_dst) {

		gameArea *myself = (gameArea*)sys->getController();
		Table *table = (Table*)sys->getUI()->getWidget("table");
		pair<int,int> source = myself->convertPosToGeneralType(org_src);
		pair<int,int> dst = myself->convertPosToGeneralType(org_dst);

		printTable(myself->getGameEngine()->local_board.get_board());
		
		if (myself->getStatus() == "waiting_for_move") {
			Player* engine = myself->getGameEngine();
			int ans = engine->move_local_token(PosType(source),PosType(dst));


			cout << "sending move " << source.first << "," << source.second << " => " << dst.first << "," << dst.second << '\n';
			if (ans == MOVE_VALID || ans == ATTACK_TRY) {
			
				//// we've got a movement!
				map <string,string> content;
				content["original_col"] = string(1,'a' + source.second );
				content["original_row"] = string(1,(char)source.first);
				content["destination_col"] = string(1,'a' +dst.second);
				content["destination_row"] = string(1,(char)dst.first);
				cout << (int)(content["original_row"][0] ) << ' ' << (int)(content["original_col"][0] - 'a') << '\n';
				cout << (int)(content["destination_row"][0] ) << ' ' << (int)(content["destination_col"][0] - 'a') << '\n';

				//cout << content["original_col"] << ' ' << content["original_row"] << ' ' << content["destination_col"] << ' ' << content["destination_row"] << '\n';

				sys->getNetwork()->sendPackage("move",content);
			}
			if (ans == ATTACK_TRY) {
				cout << "the move is an attack try! ";
				myself->setStatus("waiting_for_attack");
				myself->setCurrentMov(PosType(source),PosType(dst));
			} else if (ans == MOVE_VALID) {
				cout << "the move is normal! ";
				table->moveToken(org_src,org_dst);

				myself->setStatus("waiting_for_opp_move");
				myself->addAnimation();
				myself->removeWaitingMsg();
				myself->addWaitingMsg("Esperando al rival");
			} else {
				cout << "invalid move! \n";
			}
		}
		printTable(myself->getGameEngine()->local_board.get_board());
		
	});

}
Player *gameArea::getGameEngine() {
	return gameEngine;
}
void gameArea::setCurrentMov(PosType src,PosType dst) {
	current_src = src;
	current_dst = dst;
}
PosType gameArea::getCurrentSrc() {
	return current_src;
}
PosType gameArea::getCurrentDst() {
	return current_dst;
}
void gameArea::loadEngineContent(vector <vector <string>> &content) {
	cout << "[gameArea] loading engine content! \n";
	gameEngine->set_game_state(localStart ? LOCAL_MOVE : ENEMY_MOVE);
	for (int i = 0;i < TABLE_SLOTS;i++) {
		for (int j = 0;j < TABLE_SLOTS;j++) {
			
			if (content[i][j] != "empty") {
				if (content[i][j].substr(0,1) == "0") {
					//
				} else {
					PosType pos(convertPosToGeneralType(pair<int,int>(i,j)));
					gameEngine->local_board.set_new_token(content[i][j].substr(1,2) == "R" ? RED : BLUE,pos,stringToRank(content[i][j].substr(0,1)));
				}
			}
		}
	}
	gameEngine->local_board.set_enemy_tokens(localStart ? BLUE : RED);
	
}
pair<int,int> gameArea::convertPosToGeneralType(pair<int,int> original) {
	if (localStart) {
		return pair<int,int>(TABLE_SLOTS-original.first-1,TABLE_SLOTS-original.second-1);
	}
	return original;
}
void gameArea::addWaitingMsg(string msg) {
	if (waitingMsgAdded) return;
	screenText *text = new screenText(mySysgame,"info_text");
	pair<float,float> screenSize = view->getScreenSize();
	text->configure(msg,"roboto_v30",view->getColor("black"),pair<float,float>(halfPoint,screenSize.second / 2),1);
	addWidget((Widget*)text);

	waitingMsgAdded = 1;
}
void gameArea::removeWaitingMsg() {
	if (!waitingMsgAdded) return;

	eraseWidget("info_text");

	waitingMsgAdded = 0;
}
string gameArea::getStatus() {
	return status;
}
void gameArea::setStatus(string _status) {
	status = _status;
}
void gameArea::addOptionsButtons() {

	if (optionButtonPresent) return;
	optionButtonPresent = 1;

	pair<float,float> screenSize = view->getScreenSize();

	TextButton* randomButton = new TextButton(mySysgame,"random_button");
	randomButton->generate("AL AZAR",g_greenMedium(),pair<float,float>(threeQuartersPoint-25,screenSize.second - 220),1);
	randomButton->addIcon("icon_random");
	addWidget((TextButton*)randomButton);

	TextButton* cancelButton = new TextButton(mySysgame,"cancel_token_button");
	cancelButton->generate("VACIAR",g_redMedium(),pair<float,float>(quarterPoint+25,screenSize.second - 220),1);
	cancelButton->addIcon("icon_left");
	
	/*** ACCIONES DE LOS BOTONES CANCELAR Y RANDOM **/
	
	randomButton->onClick([](Sysgame *sys) {
		gameArea *myself = (gameArea*)sys->getController();
		myself->setRandomPieces();

	});
	
	
	cancelButton->onClick([](Sysgame *sys) {
		Table* table = (Table*)sys->getUI()->getWidget("table");
		table->clearToken();

		gameArea *myself = (gameArea*)sys->getController();

		TokenContainer *cont = (TokenContainer*)sys->getUI()->getWidget("token_container");
		if (myself->getIStart()) {
			cont->addAllRedContent();
		} else {
			cont->addAllBlueContent();
		}
		cont->generateTokenContentImage();
		myself->setTokenLeft(40);
	});
	addWidget((Widget*)cancelButton);
}
void gameArea::setRandomPieces() {
	TokenContainer *tk = (TokenContainer*)mySysgame->getUI()->getWidget("token_container");
	Table *tbl = (Table*)mySysgame->getUI()->getWidget("table");
	for (int i = 6;i < TABLE_SLOTS;i++) {
		for (int j = 0;j < TABLE_SLOTS;j++) {
			pair<int,int> pos(i,j);
			if (tbl->getPiece(pos) == "empty") {
				string next = tk->getRandomTokenAndPop();
				tbl->putToken(next,pos);
			}

		}
	}
	tk->generateTokenContentImage();
	tokensToPlace = 0;
	updateTokenMsg();

}
void gameArea::setTokenLeft(int value) {
	tokensToPlace = value;
	updateTokenMsg();
}
bool gameArea::getIStart() {
	return localStart;
}
void gameArea::removeOptionsButtons() {
	if (!optionButtonPresent) return;

	eraseWidget("random_button");
	eraseWidget("cancel_token_button");
	optionButtonPresent = 0;
}
void gameArea::removeStartButton() {
	if (!startButtonPresent) return;
	
	eraseWidget("start_button");
	 
	startButtonPresent = 0;

}
void gameArea::updateTokenMsg() {
	if (tokensToPlace == 0) {
		((screenText*)mySysgame->getUI()->getWidget("info_msg"))->changeMsg("Listo para jugar");
		addStartButton();
	} else {
		removeStartButton();
		((screenText*)mySysgame->getUI()->getWidget("info_msg"))->changeMsg("Faltan " + to_string(tokensToPlace) + " piezas");
	}

}
void gameArea::addAnimation() {
	if (animationAdded) return;

	pair<float,float> screenSize = view->getScreenSize();

	Animation *anim = new Animation(mySysgame,"animation");
	vector <string> data;
	getLoadingAImgs(data);
	anim->configure(data,pair<float,float>(halfPoint,screenSize.second/2-50),1);

	addWidget((Widget*)anim);
	animationAdded = 1;
}
void gameArea::removeAnimation() {
	if (!animationAdded) return;

	eraseWidget("animation");

	animationAdded = 0;
}

string gameArea::getSelectedItem() {
	return selectedItem;
}
void gameArea::setSelectedItem(string value) {
	 selectedItem = value;
}
void gameArea::onNetPack(string &package,map<string,string> &data) {
	cout << this->mode << ' ' << package << ' ' << this->status << '\n';
	if (this->mode == "client" && package == "r_u_ready" && this->status == "select_token") {
		this->status = "r_u_ready_recv";
		cout << "Somos clients y recibimos el r_u_ready \n";
		cout << "El juagdor no selecciono aun sus fichas, esperamos a que lo haga\n";
		cout << "status = " << this->status << '\n';
	} else if (this->mode == "client" && package == "r_u_ready" && this->status == "waiting_r_u_ready") {
		map<string,string> data;
		mySysgame->getNetwork()->sendPackage("i_am_ready",data);

		cout << "somos clientes y ya colocamos las fichas. Nos llego el r_u_ready \n!";
		if (localStart) {
			this->status = "waiting_for_move";
			removeAnimation();
			removeWaitingMsg();
			addWaitingMsg("Es tu turno");
			cout << "Como el turno inicial es mio, yo saco \n";
			cout << "status = " << this->status << '\n';
		} else {
			this->status = "waiting_for_opp_move";
			map<string,string> data;
			mySysgame->getNetwork()->sendPackage("i_am_ready",data);
			removeWaitingMsg();
			addWaitingMsg("Esperando al oponente");
			addAnimation();
			cout << "Como el turno inicial es del rival, esperamos a que juegue el oponente \n";
			cout << "Enviamos el i_am_ready \n";
			cout << "status = " << this->status << '\n';
		}
	} else if (this->mode == "server" && package == "i_am_ready" && this->status == "waiting_for_ok") {
		this->status = "waiting_for_move";
		removeAnimation();
		removeWaitingMsg();
		addWaitingMsg("Es tu turno");
		cout << "Somos servidores y recibimos el i_am_ready, y estabamos esperandolo, por lo tanto \n";
		cout << "status = " << this->status << '\n';
	}else if (this->status == "waiting_for_opp_move" && package == "move") {
		cout << "opponent move! \n";
		//cout << (int)(data["original_row"][0]-'a') << ' ' << (int)data["original_col"][0] << '\n';
		//cout << (int)(data["destination_row"][0]-'a') << ' ' << (int)data["destination_col"][0] << '\n';
		cout << (int)(data["original_row"][0] ) << ' ' << (int)(data["original_col"][0] - 'a') << '\n';
		cout << (int)(data["destination_row"][0] ) << ' ' << (int)(data["destination_col"][0] - 'a') << '\n';

		PosType src( data["original_row"][0], (int)(data["original_col"][0]-'a') );
		PosType dst( data["destination_row"][0],(int)(data["destination_col"][0]-'a') );

		current_src = src;
		current_dst = dst;

		int ans = this->gameEngine->move_enemy_token(src,dst);
		if (gameEngine->get_game_state() == WAIT_FOR_RANGE) {
			cout << "the enemy is attacking me!!!!!!! oh noooooooo!\n";
			/// Oh!!! he attacked a token
			map<string,string> dataAns;
			//this->gameEngine->process_attack(src,dst,);
			dataAns["token_rank"] = rankToString(gameEngine->local_board.get_tile(dst)->get_range());
			mySysgame->getNetwork()->sendPackage("attack",dataAns);
			this->status = "waiting_for_attack_then_play";
		} else if (ans != MOVE_VALID){
			cout << "unexcepected situation! invalid move !!";
		} else {
			Table *tbl = (Table*)getWidget("table");
			tbl->moveToken(
				convertPosToGeneralType(pair<int,int>(src.i,src.j)), 
				convertPosToGeneralType(pair<int,int>(dst.i,dst.j))
			);
			this->status = "waiting_for_move";
			removeAnimation();
			removeWaitingMsg();
			addWaitingMsg("Es tu turno");
		}
	} else if (this->status == "waiting_for_attack" && package == "attack") {
		this->status = "waiting_for_opp_move";
		cout << "we were waiting for attack result and we've got it!\n";
		string piece = data["token_rank"];
		cout << "the token is " << data["token_rank"] << '\n';

		map <string, string> sendData;
		sendData["token_rank"] = rankToString(gameEngine->local_board.get_board()[current_src.i][current_src.j]->get_range());
		mySysgame->getNetwork()->sendPackage("attack", sendData);
		cout << "sending token : " << sendData["token_rank"] << '\n';

		cout << "calling process attack. \n";
		cout << "parameters: \n";
		cout << "( " << current_src.i << ',' << current_src.j << ") (" << current_dst.i << ',' << current_dst.j << ")\n";
		cout << "token: " << stringToRank(piece) << '\n';


		////// Actualizar motor de juego

		string my_piece = rankToString(gameEngine->local_board.get_tile(current_src)->get_range());

		int res = gameEngine->process_attack(current_src,current_dst,stringToRank(piece));
		gameEngine->set_game_state(ENEMY_MOVE);
		


		////// Actualizar interfaz grafica
		removeWaitingMsg();
		addAnimation();


		addWaitingMsg("Esperando al rival");

		Table *tbl = (Table*)getWidget("table");
		tbl->takeOutToken(convertPosToGeneralType(pair<int, int>(current_src.i, current_src.j)));
		tbl->takeOutToken(convertPosToGeneralType(pair<int, int>(current_dst.i, current_dst.j)));

		string color = localStart ? "R" : "B";
		string op_color = color == "R" ? "B" : "R";

		if (res == WON) {
			string won_place = rankToString(gameEngine->local_board.get_tile(current_dst)->get_range())+ color;
			tbl->putToken( won_place,
				convertPosToGeneralType(pair<int,int>(current_dst.i,current_dst.j)
			));
			//// actualizar contador de fichas
			((TokenContainer*)getWidget("token_container_enemy"))->incContent(piece + op_color);
		} else if (res == LOSE) {
			((TokenContainer*)getWidget("token_container"))->incContent(my_piece +color);
			tbl->putToken(
				piece
				+ op_color,
				convertPosToGeneralType(pair<int,int>(current_dst.i,current_dst.j)
			));
			
		}

		

		//if (gameEngine->get_game_state() == )
	} else if (this->status == "waiting_for_attack_then_play" && package == "attack") {
		this->status = "waiting_for_move";
		cout << "we were waiting attack result and then play. We've got the attack\n";
		string piece = data["token_rank"];
		cout << "calling process attack. \n";
		cout << "parameters: \n";
		cout << "( " << current_src.i << ',' << current_src.j << ") (" << current_dst.i << ',' << current_dst.j << ")\n";
		cout << "token: " << stringToRank(piece) << '\n';

		string my_piece = rankToString(gameEngine->local_board.get_tile(current_dst)->get_range());


		int res = gameEngine->process_attack(current_src,current_dst,stringToRank(piece));
		gameEngine->set_game_state(LOCAL_MOVE);


		Table *tbl = (Table*)getWidget("table");
		tbl->takeOutToken(convertPosToGeneralType(pair<int,int>(current_src.i,current_src.j )));
		tbl->takeOutToken(convertPosToGeneralType(pair<int,int>(current_dst.i,current_dst.j )));

		string color = localStart ? "R" : "B";
		string op_color = color == "R" ? "B" : "R";

		if (res == LOSE) {
			tbl->putToken(
				rankToString(
				gameEngine->local_board.get_tile(current_dst)->get_range())
				+ (gameEngine->local_board.get_tile(current_dst)->get_player() == RED ? "R" : "B"),
				convertPosToGeneralType(pair<int,int>(current_dst.i,current_dst.j)
			));
			((TokenContainer*)getWidget("token_container_enemy"))->incContent( piece + op_color );
		} else if (res == WON) {
			tbl->putToken(
				piece
				+ (gameEngine->local_board.get_tile(current_dst)->get_player() == RED ? "R" : "B"),
				convertPosToGeneralType(pair<int,int>(current_dst.i,current_dst.j)
			));
			((TokenContainer*)getWidget("token_container"))->incContent( my_piece + color );
		}

		removeWaitingMsg();
		removeAnimation();
		addWaitingMsg("Es tu turno");

	} else {
		cout << "unexpected package! \n";
	}
} // handle NETWORK actions
void gameArea::onNetEvent(NETWORK_EVENT *ev) {
	if (ev->msg == "connlost") {
		mySysgame->setNewController(new connectionLostMenu(mySysgame));
	}
}

gameArea::~gameArea() {
	delete gameEngine;
}
