#pragma once
#include "BasicToken.h"

#define BOARD_SIZE 10

class GameBoard
{
public:
	GameBoard();
	BasicToken** get_board();
	void set_tile(PosType token_pos, BasicToken* token);
	~GameBoard();
private:
	BasicToken * board[BOARD_SIZE][BOARD_SIZE];
};

