#pragma once
#include "BasicToken.h"

#define BOARD_SIZE 10

class GameBoard // Se usa luego como otra parte de Player
{
public:
	GameBoard(); /// Se inicializa vacio
	BasicToken** get_board(); /// Retorna un puntero al tablero
	void set_new_token(PlayerType owner, PosType pos, RangeType rank);
	void move_token(PosType src_pos, PosType dst_pos); /// Mueve una ficha de src a dst con el movimiento YA validado
	RangeType get_token_range(PosType token_pos);
	~GameBoard();
private:
	BasicToken * board[BOARD_SIZE][BOARD_SIZE];
};

