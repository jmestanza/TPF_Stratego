#pragma once
#include "BasicToken.h"

#define BOARD_SIZE 10


typedef vector<vector<BasicToken*>> tablero_t;

class GameBoard // Se usa luego como otra parte de Player
{
public:
	GameBoard(); /// Se inicializa vacio
	tablero_t& get_board(); /// Retorna un puntero al tablero

	BasicToken* get_tile(PosType tile); /// Retorna un puntero a una ficha del tablero, o nullptr si esta vacia
	void set_new_token(PlayerType owner, PosType pos, RangeType rank); /// Crea una nueva ficha en el tablero
	void set_enemy_tokens(PlayerType enemy_color); /// Rellena los lugares de las fichas enemigas con {RangeType: ENEMY, PlayerType: enemy_color}
	void clear_tile(PosType tile_pos); /// Elimina una ficha del tablero
	void move_token(PosType src_pos, PosType dst_pos); /// Mueve una ficha de src a dst con el movimiento YA validado
	~GameBoard();
private:
	tablero_t board;
//	BasicToken * board[BOARD_SIZE][BOARD_SIZE];
};

