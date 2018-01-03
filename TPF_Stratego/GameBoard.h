#pragma once
#include "BasicToken.h"

#define BOARD_SIZE 10

class GameBoard // Se usa luego como otra parte de Player
{
public:
	GameBoard(); /// Se inicializa vacio
	BasicToken** get_board(); /// Retorna un puntero al tablero
	BasicToken* get_tile(PosType tile); /// Retorna un puntero a una ficha del tablero, o nullptr si esta vacia
	void set_new_token(PlayerType owner, PosType pos, RangeType rank); /// Crea una nueva ficha en el tablero
	void clear_tile(PosType tile_pos);
	void move_token(PosType src_pos, PosType dst_pos); /// Mueve una ficha de src a dst con el movimiento YA validado
	~GameBoard();
private:
	BasicToken * board[BOARD_SIZE][BOARD_SIZE];
};

