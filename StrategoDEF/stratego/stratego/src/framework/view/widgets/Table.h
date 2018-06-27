#pragma once

// Table: representa el tablero del juego, 
// Tiene callbacks que se llaman cuando se presionan sus casilleros, y funciones
// para actualizar las fichas que muestra. No tiene gran inteligencia, es parte de la vista.
// La idea es que el controller decida como actuar ante las acciones ejercidas sobre el tablero.


#include <framework\view\allegro_manager\allegro_manager.h>
#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\TokenContainer\TokenContainer.h>

#include "widget.h"
#include "screen_text.h"
#include "music_button.h"
#include <iostream>

#define TABLE_SLOTS 10

enum { IDLE,BUTTON_DOWN,BUTTON_UP };

using namespace std;

class TableException : public exception {
private:
	string err;
public:
	TableException(string er);
	virtual const char *what() const throw();

};

class TokenContainer;

class Table : public Widget {
	public:
		Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float>_pieceSize,int mode);
		int mode;
		int status;
		bool src_txt_ready;
		bool dst_txt_ready;
		bool lps_created;
		int mx,my;
		string upPlayer,downPlayer;

		string img_a;
		string img_b;
		string myCode;
		string fieldACode,fieldBCode;
		string selectedPiece;

		string gameStatus;
		pair<float,float> screen_center;
		map<pair<int,char>,int> ind_table;
		pair <int,int> pieceSize;
		pair<int,int> selectedPosition;
		int isSelected;

		screenText *SelectedPosText;
		screenText *OnActionText;
	
		music_button *loopsound;

		int underAnimation;
		string animatedBitmap;

		vector < vector <string> > shownTokens; /// shown tokens per position
		//vector < vector <string> > allowedModify;
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void setPlayersName(string upPlayer,string downPlayer);
		

		void takeOutToken(pair<int,int> position); // sacar ficha del tablero
		void putToken(string code,pair<int,int> position); //agregar ficha
		
		bool insideGameboard(int x,int y);

		void moveToken(pair<int,int> posA,pair<int,int> posB); // mover ficha 
		string getPosCode(pair<int,int> pos);
		void informSelected(string piece);
		string getPiece(pair<int,int> pos);
		void freePosition(pair<int,int> pos); // sacar fich

		TokenContainer * refContainer;
		void setTokenContainer(TokenContainer *tok);

		~Table();
		void setStatus(string _status);
		void fillOpponentField(string color);

		void onMouseRelease(void (*func)(Sysgame*,Table*,pair<int,int>)); // cuando se suelta un casillero
		void onMousePress(void(*func)(Sysgame*,Table*,pair<int,int>)); // cuando se presiona un casillero
		void onActionMove(void(*func)(Sysgame*,Table*,pair<int,int>,pair<int,int>)); // cuando se presiona una secuencia de casilleros ( se hace un movimiento)

		void clearToken(); //borrar todas las fichas
		vector <vector<string>>& getContent();

	private:
		/// funciones de los callback
		void (*onMouseReleasedFunction)(Sysgame *,Table *,pair<int,int>);
		void (*onMousePressFunction)(Sysgame *,Table *,pair<int,int>);
		void (*onActionMoveFunction)(Sysgame*,Table*,pair<int,int>,pair<int,int>);
		
};

