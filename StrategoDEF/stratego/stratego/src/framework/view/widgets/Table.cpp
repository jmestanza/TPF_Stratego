#include "Table.h"

#include <framework/utils/random_number.h>
#include <framework/view/utils/copyBitmap.h>
#include <game/utils/genTokenImages.h>

Table::Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float>_pieceSize,int _mode) :Widget(Sys,_name) {

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

	myCode = "table_" + to_string(randomNumber());

	for (int i = 0;i < TABLE_SLOTS;i++) shownTokens.push_back(vector<string>(TABLE_SLOTS,"empty"));

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

	drawToken("1B",pair<int,int>(4,4));
	drawToken("2B",pair<int,int>(4,5));
	drawToken("3B",pair<int,int>(4,6));
}
void Table::handleEvent(ALLEGRO_EVENT *ev) {

	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		status = BUTTON_DOWN;
	} else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		status = BUTTON_UP;
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
void Table::drawToken(string code,pair<int,int> position) {
	pair<int,int> realPosition(position);
	realPosition.first *= 60;
	realPosition.second *= 60;
	realPosition.first += pos.first;
	realPosition.second += pos.second;

	view->show("token_" + code + "_r",getPosCode(position),realPosition.first,realPosition.second);

}
string Table::getPosCode(pair<int,int> position) {
	return "piece_" + to_string(position.first) + "_" + to_string(position.second);
}
void Table::eraseToken(pair<int,int> position) {

}
void Table::moveToken(pair<int,int> posA,pair<int,int> posB) {

}

void Table::stopDrawing() {

}
Table::~Table() {

}

TableException::TableException(string er) :err(er) {

}

const char* TableException::what() const throw() {
	return err.c_str();
}