#pragma once

#include <framework\view\allegro_manager\allegro_manager.h>
#include <framework\sysgame\sysgame.h>
#include <framework\view\widgets\TokenContainer\TokenContainer.h>

#include "widget.h"
#include "TableButton.h"
#include <iostream>

#define TABLE_SLOTS 10
#define INT_OUT_OF_RANGE 10000
#define CHAR_OUT_OF_RANGE 'Z'

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
		//Table(Viewer* _view, pair <float,float> screen_center, pair<float, float>_pieceSize);
		Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float>_pieceSize,int mode);
		int mode;
		int status;
		int mx,my;
		string upPlayer,downPlayer;

		string img_a;
		string img_b;
		string myCode;
		string fieldACode,fieldBCode;
		string selectedPiece;

		string gameStatus;
		pair<float,float> fakesize;
		pair<float,float> screen_center;
		vector<TableButton> t_table;
		map<pair<int,char>,int> ind_table;
		pair <int,int> pieceSize;
		pair<int,char> WhoIsInRange(pair<float,float> _mousepos);
		pair<int,int> selectedPosition;
		int isSelected;
		
		int underAnimation;
		string animatedBitmap;

		vector < vector <string> > shownTokens; /// shown tokens per position
		//vector < vector <string> > allowedModify;
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void setPlayersName(string upPlayer,string downPlayer);

		void takeOutToken(pair<int,int> position);
		void putToken(string code,pair<int,int> position);
		void eraseToken(pair<int,int> position);
		void moveToken(pair<int,int> posA,pair<int,int> posB);
		string getPosCode(pair<int,int> pos);
		void informSelected(string piece);
		string getPiece(pair<int,int> pos);
		void freePosition(pair<int,int> pos);

		TokenContainer * refContainer;
		void setTokenContainer(TokenContainer *tok);

		~Table();
		void setStatus(string _status);
		void fillOpponentField(string color);

		void onMouseRelease(void (*func)(Sysgame*,Table*,pair<int,int>));
		void onMousePress(void(*func)(Sysgame*,Table*,pair<int,int>));
		void onActionMove(void(*func)(Sysgame*,Table*,pair<int,int>,pair<int,int>));

		void clearToken();
		vector <vector<string>>& getContent();

	private:
		void (*onMouseReleasedFunction)(Sysgame *,Table *,pair<int,int>);
		void (*onMousePressFunction)(Sysgame *,Table *,pair<int,int>);
		void (*onActionMoveFunction)(Sysgame*,Table*,pair<int,int>,pair<int,int>);
		
};

