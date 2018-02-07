#include "Table.h"

ostream& operator<< (ostream& os, map<string, string>&content) {
	cout << "{";
	for (auto it = content.begin(); it != content.end(); it++) {
		cout << it->first << ":" << it->second;
		if (it != prev(content.end())) cout << ",";
	}
	cout << "}";
	return os;
}
Table::Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float> _screen_center,pair<float,float>_pieceSize):Widget(Sys, _name)
{
/*
if (1) {  throw TableException("hubo un error");	}
*/
	Viewer* _view =	mySysgame->getAllegroHandler();
	
	img_a = _img_a; // set image for buttons at the beginning
	img_b = _img_b;

 	status = IDLE;
	screen_center = _screen_center;
	size.first = _pieceSize.first;
	size.second = _pieceSize.second;
	fakesize.first = size.first + 2; // El +2 es para que se distingan los rectángulos
	fakesize.second = size.second + 2;  

	for (int i = 0; i < TABLE_SLOTS; i++) {
		for (int j = 0; j < TABLE_SLOTS; j++) {
			pair<float, float> aux_pos = pair<float, float>(i * fakesize.first, j * fakesize.second);
			string aux_name = "button" + to_string(i) + char( 'A'+j );
			t_table.push_back(TableButton(_img_a, aux_pos, size, Sys , aux_name));
			ind_table[pair<int, char>(i, 'A' + j)] = t_table.size()-1;
			cout << "AUXPOS:" <<  aux_pos.first << " " << aux_pos.second << endl;
			view->show(_img_a,aux_name, aux_pos.first, aux_pos.second);
		}
	}
}

pair<int, char> Table::WhoIsInRange(pair<float, float> _mousepos)
{ 
	// este tiene que ser con el size ficticio
	//first = X second =Y
	int hor = int(   _mousepos.first / fakesize.first );
	char vert = 'A' + int(_mousepos.second / fakesize.second);

	if (ind_table.find(pair<int, char>(hor, vert)) != ind_table.end()) {
		return pair<int, char>(hor, vert);
	}
	else {
		return pair<int, char>(10000, 'Z'); // no esta en el mapa
	}

}

void Table::handleEvent(ALLEGRO_EVENT *ev) {

	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		status = BUTTON_DOWN;
	}
	else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		status = BUTTON_UP;
	}
	
	float pos_x = ev->mouse.x;
	float pos_y = ev->mouse.y;


	if (status == BUTTON_UP) {
	
	}
	else if (status == BUTTON_DOWN) {
		pair<int, char> TheChosenOne = WhoIsInRange(pair<float, float>(pos_x, pos_y));
		cout << "INT: " << TheChosenOne.first << "CHAR: " << TheChosenOne.second << endl;
		string aux_Chosen = "button" + to_string(TheChosenOne.first) + TheChosenOne.second ;
		try {
			view->changeShowImg(aux_Chosen, img_b);
		}
		catch (exception &e) {
			cout << e.what() << endl;
		}

	}
}
Table::~Table()
{

}

TableException::TableException(string er):err(er)
{

}

const char* TableException::what() const throw() {
	return err.c_str();
}