#include "Table.h"

#include <framework/utils/random_number.h>
#include <framework/view/utils/copyBitmap.h>
#include <game/utils/genTokenImages.h>

Table::Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float>_pieceSize,int _mode) :Widget(Sys,_name) {

	gameStatus = "choosing_pieces";
	selectedPiece = "";

	Viewer* _view = mySysgame->getAllegroHandler();

	img_a = _img_a; // set image for buttons at the beginning
	img_b = _img_b;

	status = IDLE;
	//screen_center = _screen_center;
	size.first = _pieceSize.first;
	size.second = _pieceSize.second;
	fakesize.first = size.first + 2; // El +2 es para que se distingan los rectángulos
	fakesize.second = size.second + 2;

	mode = _mode;
	this->size = pair<float,float>(_pieceSize.first * 10,_pieceSize.second * 10);
	
	this->pieceSize = _pieceSize;


	myCode = "table_" + to_string(randomNumber());

	for (int i = 0;i < TABLE_SLOTS;i++) shownTokens.push_back(vector<string>(TABLE_SLOTS,"empty"));

	onMouseReleasedFunction = nullptr;
	onMousePressFunction = nullptr;
	onActionMoveFunction = nullptr;
}

pair<int,char> Table::WhoIsInRange(pair<float,float> _mousepos) {
	// este tiene que ser con el size ficticio
	//first = X second =Y
	int hor = int(_mousepos.first / fakesize.first);
	char vert = 'A' + int(_mousepos.second / fakesize.second);

	if (ind_table.find(pair<int,char>(hor,vert)) != ind_table.end()) {
		return pair<int,char>(hor,vert);
	} else {
		return pair<int,char>(INT_OUT_OF_RANGE,CHAR_OUT_OF_RANGE); // no esta en el mapa
	}

}
void Table::setPlayersName(string _upPlayer,string _downPlayer) {
	upPlayer = _upPlayer;
	downPlayer = _downPlayer;
}
void Table::setStatus(string _status) {
	gameStatus = _status;
}
void Table::startDrawing() {

	pair <float,float> fieldSize(al_get_bitmap_width(view->getImg("blue_field")),al_get_bitmap_height(view->getImg("blue_field")));

	int xUp = this->pos.first + this->size.first - fieldSize.first - 20;
	int yUp = this->pos.second - fieldSize.second;

	int xDown = this->pos.first + 20;
	int yDown = this->pos.second + this->size.second;

	ALLEGRO_BITMAP *upField = copyBitmap(view->getImg("red_field"));
	ALLEGRO_BITMAP *downField = copyBitmap(view->getImg("blue_field"));

	if (this->mode == 1) {
		ALLEGRO_BITMAP *aux = upField;
		upField = downField;
		downField = aux;
	}


	blitTextCentered(view,upField,upPlayer,"roboto_v1","white");
	blitTextCentered(view,downField,downPlayer,"roboto_v1","white");

	fieldACode = "up_field_" + myCode;
	fieldBCode = "down_field_" + myCode;

	view->loadFromBitmap(upField,fieldACode);
	view->loadFromBitmap(downField,fieldBCode);
	view->show(fieldACode,fieldACode,xUp,yUp);
	view->show(fieldBCode,fieldBCode,xDown,yDown);

	genTokenImages(view);

	view->show("table","table",this->pos.first,this->pos.second);

	/*for (int i = 0; i < TABLE_SLOTS; i++) {
	for (int j = 0; j < TABLE_SLOTS; j++) {
	pair<float,float> aux_pos = pair<float,float>(i * fakesize.first,j * fakesize.second);
	string aux_name = "button" + to_string(i) + char('A' + j);
	t_table.push_back(TableButton(img_a,aux_pos,size,mySysgame,aux_name));
	ind_table[pair<int,char>(i,'A' + j)] = t_table.size() - 1;*/


	//view->show(img_a,aux_name,aux_pos.first,aux_pos.second);
	/*	}
	}*/

	/*putToken("1B",pair<int,int>(4,4));
	putToken("2B",pair<int,int>(4,5));
	putToken("3B",pair<int,int>(4,6));*/
}
void Table::fillOpponentField(string color) {
	for (int i = 0;i <= 3;i++) {
		for (int j = 0;j < TABLE_SLOTS;j++) {
			putToken("0"+color,pair<int,int>(i,j));
		}
	}
}
void Table::clearToken() {
	for (int i = 0;i < TABLE_SLOTS;i++) {
		for (int j = 0;j < TABLE_SLOTS;j++) {
			freePosition(pair<float,float>(i,j));
		}
	}
}
void Table::handleEvent(ALLEGRO_EVENT *ev) {

	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		status = BUTTON_DOWN;
		int rx,ry;
		rx = mx - this->pos.first;
		ry = my - this->pos.second;
		if (insideMe(rx,ry)) {

			rx /= this->pieceSize.first;
			ry /= this->pieceSize.second;

			if (onMousePressFunction != nullptr) {

				this->onMousePressFunction(mySysgame,this,pair<int,int>(ry,rx));
			}
			
		}
	} else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		status = BUTTON_UP;

		//if (this->gameStatus == "choosing_pieces") {
		int rx,ry;
		rx = mx - this->pos.first;
		ry = my - this->pos.second;
		if (insideMe(rx,ry)) {
				
			rx /= this->pieceSize.first;
			ry /= this->pieceSize.second;
				
			if (onMouseReleasedFunction != nullptr) {
				this->onMouseReleasedFunction(mySysgame, this, pair<int, int>(ry, rx));
			}
			if (!isSelected) {
				selectedPosition = pair<int,int>(ry,rx);
				isSelected = 1;
				cout << "selected => ("<<selectedPosition.first<<","<<selectedPosition.second<<")\n"; 
			} else {
				cout << "action " << "("<<selectedPosition.first<<","<<selectedPosition.second<<") -> ("<<ry<<","<<rx<<")\n";
				if (onActionMoveFunction != nullptr) {
					onActionMoveFunction(mySysgame,this,selectedPosition,pair<int,int>(ry,rx));
				}
				isSelected = 0;
			}
				/*if (ry >= 6) { /// only upside is allowed
					if (this->selectedPiece != "") {
						this->putToken(this->selectedPiece,pair<int,int>(rx,ry));

						this->selectedPiece = "";
					}
				}*/
			//}
		}

	} else if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mx = ev->mouse.x;
		my = ev->mouse.y;
	}

	float pos_x = ev->mouse.x;
	float pos_y = ev->mouse.y;


	if (status == BUTTON_UP) {

	} else if (status == BUTTON_DOWN) {
		pair<int,char> TheChosenOne = WhoIsInRange(pair<float,float>(pos_x,pos_y));
		string aux_Chosen = "button" + to_string(TheChosenOne.first) + TheChosenOne.second;

		try {
			if (TheChosenOne != pair<int,char>(INT_OUT_OF_RANGE,CHAR_OUT_OF_RANGE)) {

			}
			//view->changeShowImg(aux_Chosen, img_b);
		} catch (exception &e) {
			cout << e.what() << endl;
		}

		try {
			//view->playonce("sonic");
		} catch (exception &e) {
			cout << e.what() << endl;
		}
	}
}
string Table::getPiece(pair<int,int> pos) {
	return shownTokens[pos.first][pos.second];
}
void Table::freePosition(pair<int,int> pos) {
	if (shownTokens[pos.first][pos.second] != "empty") {
		view->stopShow(getPosCode(pos));
	}
	shownTokens[pos.first][pos.second] = "empty";
}
void Table::putToken(string code,pair<int,int> position) {
	if (shownTokens[position.first][position.second] != "empty") {
		view->stopShow(getPosCode(position));
	}

	shownTokens[position.first][position.second] = code;

	pair<int,int> realPosition(position);
	realPosition.first *= 60;
	realPosition.second *= 60;
	realPosition.first += pos.second;
	realPosition.second += pos.first;

	view->show("token_" + code + "_r",getPosCode(position),realPosition.second,realPosition.first);

}
string Table::getPosCode(pair<int,int> position) {
	return "piece_" + to_string(position.second) + "_" + to_string(position.first);
}
void Table::takeOutToken(pair<int,int> position) {
	if (shownTokens[position.first][position.second] != "") {
		view->stopShow(getPosCode(position));
	}
}
void Table::moveToken(pair<int,int> posA,pair<int,int> posB) {
	//underAnimation = 1;
	if (shownTokens[posA.first][posA.second] == "empty") return;
	shownTokens[posB.first][posB.second] = shownTokens[posA.first][posA.second];
	shownTokens[posA.first][posA.second] = "empty";
}

void Table::stopDrawing() {

}

void Table::informSelected(string _sel) {
	selectedPiece = _sel;
}
void Table::onActionMove(void(*func)(Sysgame*,Table*,pair<int,int>,pair<int,int>)) {
	onActionMoveFunction = func;
}
Table::~Table() {

}
void Table::setTokenContainer(TokenContainer *tok) {
	refContainer = tok;
}
void Table::onMouseRelease(void (*func)(Sysgame*,Table*,pair<int,int>)) {
	onMouseReleasedFunction = func;
}
void Table::onMousePress(void(*func)(Sysgame*,Table*,pair<int,int>)) {
	onMousePressFunction = func;
}
vector <vector<string>>& Table::getContent() {
	return shownTokens;
}
TableException::TableException(string er) :err(er) {

}

const char* TableException::what() const throw() {
	return err.c_str();
}