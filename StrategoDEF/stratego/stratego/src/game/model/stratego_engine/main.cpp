#include <stdio.h>
#include <tchar.h>
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
				//cout << tablero[i][j]->get_player();
			}
		}	cout << endl;
	}
}


// COMENTARIOS Y GENERALIDADES SOBRE LAS PRUEBAS DE ESTE CODIGO:
// (cosas que se podrían mejorar, también)
// 0 tira reselect? (si muevo 1 a la derecha) wtf 
// ah, en general tira reselect antes de que quieras mover la ficha a un lugar donde ya hay una,
// pero  primero deberia saltar que no la podes mover...

// arreglar el ataque... parece que tienen que estar contiguos para atacar (ver scout)
// queda ver como funcionan los estados del juego

//en PosType cambie de x y a i j dado que el tablero se maneja como una matriz
//entonces me parecía conveniente hacerlo de esa manera

//se probo atacar contiguamente


void tablero_init(Player& p1,RangeType range){
	PosType aux;
	for (int i = 6; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (((p1.local_board.get_board()))[i][j] == nullptr) {
				aux.i = i;
				aux.j = j;
				p1.local_board.set_new_token(BLUE,aux,range); // range+1 porque puedo poner 0-9 no 10
			} else {
				cout << "la ficha ya ha sido asignada" << endl;
				// RECORDAR: YA ESTAN ASIGNADAS LAS DEL ENEMIGO EN MI TABLERO
			}
		}
	}
}

int main()
{

	Player p1(BLUE);
	RangeType range = 9;

	tablero_init(p1,range); // para las pruebas pongo todos con el mismo rango
	
	PosType src;
	PosType dst;

	//	MOVE_VALID = 1,MOVE_NOT_VALID,RESELECT,ATTACK_TRY,ERROR
	//	ENEMY = 0,MARSHAL 1,GENERAL 2,COLONEL 3 ,MAJOR 4,CAPTAIN 5,LIEUTENANT 6,SERGEANT 7,
	//  MINER 8,SCOUT 9,SPY 10 ,BOMB 11 ,FLAG 12


	// PLAYER - Guia general //
	// --------------------- //
	/// 1. Para ubicar las fichas locales al inicio, para cada una se debe usar el metodo 
	///    incluido en el objeto GameBoard -> set_new_token. Las fichas enemigas se ubican 
	///    por si solas segun corresponda el color con el rango ENEMY (ver en BasicToken).
	/// 2. En el turno del jugador local (LOCAL_MOVE), una vez definido el movimiento se 
	///    llama al metodo move_local_token con los parametros indicados, el cual lo evalua
	///    y devuelve el resultado correspondiente segun MoveTypes.
	/// 3. En caso de ser un movimiento normal, va a cambiar al estado ENEMY_MOVE, donde se
	///    esperara a recibir el proximo paquete de movimiento enemigo, que se procesa con
	///    el metodo move_enemy_token con los parametros indicados, el cual lo evalua y 
	///    devuelve el resultado correspondiente segun MoveTypes.
	/// 4. Con movimientos normales, 2. y 3. se repiten indefinidamente.
	/// 5. Si de evaluar el movimiento en algun caso resulta un ATTACK_TRY, tanto en el caso
	///    de origen local hacia el enemigo como del enemigo hacia el local, cuando ya se 
	///    enviaron los paquetes ATTACK a ambos lados, se llama al metodo process_attack para
	///    que lo resuelva.
	///

	bool end = false;
	p1.set_game_state(LOCAL_MOVE);
	RangeType range_from_network = 1; // este es el rango que viene via networking
	char c=0;

	while(!end){

		cout << "TABLERO 1: " << endl; 	printTable(p1.local_board.get_board());
		cout << "TURNO de J" << p1.get_game_state() << endl;
		c = getchar(); src.i = int(c - '0');
		c = getchar(); src.j = int(c - '0');
		c = getchar(); dst.i = int(c - '0');
		c = getchar(); dst.j = int(c - '0');		
		c=getchar();
		cout << "source:" << "[" << src.i << "]" << "[" << src.j << "]" << endl;
		cout << "dst:" << "[" << dst.i << "]" << "[" << dst.j << "]" << endl;
		
		switch(p1.get_game_state()){
			case LOCAL_MOVE:
				switch(p1.move_local_token(src,dst)){
				case MOVE_VALID:
					cout << "valid move!" << endl;
					break;
				case ATTACK_TRY:
					cout << "attack_try" << endl;
					break;
				case MOVE_NOT_VALID:
					cout << "move not valid " << endl;
					break;
				case RESELECT:
					cout << "reselect" << endl;
					break;
				};		
				break;
			case ENEMY_MOVE:
				switch(p1.move_enemy_token(src,dst)){
				case MOVE_VALID:
					cout << "valid enemy move!" << endl;
					break;
				case ATTACK_TRY:
					p1.process_attack(src,dst,p1.local_board.get_board()[dst.i][dst.j]->get_range());
					cout << "hay que implementar el ataque enemigo" << endl;
					break;
				case MOVE_NOT_VALID:
					cout << "enemy move not valid " << endl;
					break;
				case RESELECT:
					cout << "enemy reselect" << endl;
					break;
				};
			break;	
		};
		if(p1.get_game_state() == WAIT_FOR_RANGE){
			p1.process_attack(src,dst,range_from_network);
			p1.set_game_state(ENEMY_MOVE);
		}
	}
    return 0;
}
