#pragma once
#include "BasicToken.h"

#define BOARD_SIZE 10

class GameBoard // Se usa luego como otra parte de Player
{
public:
	GameBoard(); /// Se inicializa vacio
	BasicToken** get_board();
	void set_new_token(PosType pos, RangeType rank);
	~GameBoard();
private:
	BasicToken * board[BOARD_SIZE][BOARD_SIZE];
};

