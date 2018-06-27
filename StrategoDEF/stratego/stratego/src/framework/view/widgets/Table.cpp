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

	mode = _mode;
	this->size = pair<float,float>(_pieceSize.first * 10,_pieceSize.second * 10);
	
	this->pieceSize = _pieceSize;

	src_txt_ready = 0;
	dst_txt_ready = 0;

	myCode = "table_" + to_string(randomNumber());

	for (int i = 0;i < TABLE_SLOTS;i++) shownTokens.push_back(vector<string>(TABLE_SLOTS,"empty"));

	onMouseReleasedFunction = nullptr;
	onMousePressFunction = nullptr;
	onActionMoveFunction = nullptr;
	lps_created = false;
	loopsound=nullptr;
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

}
void Table::fillOpponentField(string color) {
	for (int i = 0;i < 4;i++) {
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
		pair<float,float> screenSize = view->getScreenSize();
		if (!lps_created) {
			lps_created = true;
			loopsound = new music_button(mySysgame,pair<float,float>(screenSize.first - 500,screenSize.second / 16),"trigger_sound","sound_on");
			loopsound->startDrawing();
			mySysgame->getAllegroHandler()->playloop("one_piece_tvvs");
			mySysgame->getAllegroHandler()->set_is_looping(true);
			loopsound->onClick([](Sysgame *sys) {
				cout << "se llamo al on click" << endl;
				if (sys->getAllegroHandler()->get_is_looping()) {
					sys->getAllegroHandler()->changeShowImg("trigger_sound","sound_off");
					sys->getAllegroHandler()->stopsample("one_piece_tvvs");
					sys->getAllegroHandler()->set_is_looping(false);
				} else {
					sys->getAllegroHandler()->changeShowImg("trigger_sound","sound_on");
					sys->getAllegroHandler()->playloop("one_piece_tvvs");
					sys->getAllegroHandler()->set_is_looping(true);
				}
			});
		}
		if (lps_created && loopsound != nullptr) {
			cout << "HOLASASDASDASDSASFDF" << endl;
			if (loopsound->insideIconRange(rx,ry)) {
				cout << "esta en rango deberia funcionar!" << endl;
				loopsound->onClickFunction(this->mySysgame);
			}
		}

		if (insideGameboard(rx,ry)) {

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
		pair<float,float> screenSize = view->getScreenSize();
		//	
		if (insideGameboard(rx,ry)) {
				
			rx /= this->pieceSize.first;
			ry /= this->pieceSize.second;
			if (mySysgame->isValidPos(pair<int,int>(ry,rx))){
				if (onMouseReleasedFunction != nullptr) {
					this->onMouseReleasedFunction(mySysgame,this,pair<int,int>(ry,rx));
				}

				//verificar que se pueden borrar
				if(src_txt_ready && dst_txt_ready){
					mySysgame->getController()->eraseWidget("selected_text");
					mySysgame->getController()->eraseWidget("onaction_text");
					src_txt_ready = 0;
					dst_txt_ready = 0;
				}
				
				//no olvidar borrar esto de la memoria
				// Estoy trabajando en esto por favor NO BORRAR 
				
				

				if (!isSelected) {
					mySysgame->getAllegroHandler()->playonce("piece_up");
					selectedPosition = pair<int,int>(ry,rx);
					isSelected = 1;
					cout << "selected => (" << selectedPosition.first << "," << selectedPosition.second << ")\n";
					string SelectedPosStr = "src:"+(to_string(selectedPosition.first)+ to_string(selectedPosition.second));
					if(!src_txt_ready){
						SelectedPosText = new screenText(mySysgame,"selected_text");
						SelectedPosText->configure(SelectedPosStr,"roboto_v30",view->getColor("black"),pair<float,float>(800,screenSize.second / 2 + 50),1);
						mySysgame->getController()->addWidget((Widget*)SelectedPosText);
						src_txt_ready=1;
					}
					
				} else {
					mySysgame->getAllegroHandler()->playonce("piece_down");
					if(!dst_txt_ready){
						string SelectedPosStr = "dst:" + (to_string(ry) + to_string(rx));
						OnActionText = new screenText(mySysgame,"onaction_text");
						OnActionText->configure(SelectedPosStr,"roboto_v30",view->getColor("black"),pair<float,float>(1000,screenSize.second / 2 + 50),1);
						mySysgame->getController()->addWidget((Widget*)OnActionText);
						dst_txt_ready=1;
					}
					
					cout << "action " << "(" << selectedPosition.first << "," << selectedPosition.second << ") -> (" << ry << "," << rx << ")\n";
					
					if (onActionMoveFunction != nullptr) {
						onActionMoveFunction(mySysgame,this,selectedPosition,pair<int,int>(ry,rx));
					}
					isSelected = 0;
				}
			}else{
				cout << " NOT VALID POS " << endl;
			}
		}
	} else if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mx = ev->mouse.x;
		my = ev->mouse.y;
	}

	float pos_x = ev->mouse.x;
	float pos_y = ev->mouse.y;

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
bool Table::insideGameboard(int x,int y) {
	return ((x >= (pos.first - 20)) && (x <= (pos.first + size.first - 22)) && (y >= (pos.second - 50)) && (y <= (pos.second + size.second - 40)));
}
string Table::getPosCode(pair<int,int> position) {
	return "piece_" + to_string(position.second) + "_" + to_string(position.first);
}
void Table::takeOutToken(pair<int,int> position) {
	if (shownTokens[position.first][position.second] != "empty") {
		view->stopShow(getPosCode(position));
		shownTokens[position.first][position.second] = "empty";
	}
}
void Table::moveToken(pair<int,int> posA,pair<int,int> posB) {
	//underAnimation = 1;
	if (shownTokens[posA.first][posA.second] == "empty") return;

	putToken(shownTokens[posA.first][posA.second], posB);
	takeOutToken(posA);

	//shownTokens[posB.first][posB.second] = shownTokens[posA.first][posA.second];
	//shownTokens[posA.first][posA.second] = "empty";


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