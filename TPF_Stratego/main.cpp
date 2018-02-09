#include "stdafx.h"
#include <iostream>
#include "Player.h"
#include <string>

using namespace std;

void printTable(tablero_t& tablero){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j= 0; j < BOARD_SIZE ; j++){
			if(tablero[i][j] == nullptr){
				cout << "N";
			}else{
				cout << tablero[i][j]->get_range();
			}
		}	cout << endl;
	}
}

int main()
{

	Player p1(BLUE);
	Player p2(RED);
	RangeType range = 1;

	PosType aux;
	for (int i = 6; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
			if (((p1.local_board.get_board()))[i][j] == nullptr) {
					aux.x=i;
					aux.y=j;
					p1.local_board.set_new_token(BLUE,aux,range); // range+1 porque puedo poner 0-9 no 10
			} else {
				cout << "la ficha ya ha sido asignada" << endl;
				// RECORDAR: YA ESTAN ASIGNADAS LAS DEL ENEMIGO EN MI TABLERO
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (((p2.local_board.get_board()))[i][j] == nullptr) {
				aux.x = i;
				aux.y = j;
				p2.local_board.set_new_token(RED,aux,range); // range+1 porque puedo poner 0-9 no 10
			} else {
				cout << "la ficha ya ha sido asignada" << endl;
				// RECORDAR: YA ESTAN ASIGNADAS LAS DEL ENEMIGO EN MI TABLERO
			}
		}
	}
	
	bool end=false;
	
	State game_stp1 = LOCAL_MOVE;
	State game_stp2 = ENEMY_MOVE;
	p1.set_game_state(game_stp1);
	p2.set_game_state(game_stp2);
	

	PosType src;
	PosType dst;

	src.x=6;
	src.y=0;
	dst.x=5;
	dst.y=0;
	
	//	MOVE_VALID = 1,MOVE_NOT_VALID,RESELECT,ATTACK_TRY,ERROR
	//enum Ranges {
	//	ENEMY = 0,MARSHAL 1,GENERAL 2,COLONEL 3 ,MAJOR 4,CAPTAIN 5,LIEUTENANT 6,SERGEANT 7,MINER 8,SCOUT 9,
	//	SPY 10 ,BOMB 11 ,FLAG 12
	//};
	if(p1.move_local_token(src,dst)==MOVE_VALID){
		cout << "mov valid! ;)" << endl;
	}else if(p1.move_local_token(src,dst)==MOVE_NOT_VALID){
		cout << "move not valid! :(" << endl;
	} else if (p1.move_local_token(src,dst) == RESELECT) {
		cout << "reselect! :(" << endl;
	} else if (p1.move_local_token(src,dst) == ATTACK_TRY) {
		cout << "attack_try! :(" << endl;
	} else if (p1.move_local_token(src,dst) == ERROR) {
		cout << "error! :(" << endl;
	}

	cout << "TABLERO 1: " << endl;
	printTable(p1.local_board.get_board());
	cout << "TABLERO 2:" << endl;
	printTable(p2.local_board.get_board());

	// queda adaptar lo de marce... ver el define extraño que uso
	system("pause");
    return 0;
}
