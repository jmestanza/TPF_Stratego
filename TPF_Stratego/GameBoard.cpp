#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = nullptr;
		}
	}
}

BasicToken ** GameBoard::get_board()
{
	return &board[0][0];
}

void GameBoard::set_new_token(PosType pos, RangeType rank)
{
	if ((rank == FLAG) || (rank == BOMB)) {
		board[ADJ_COORD(pos.x)][ADJ_COORD(pos.y)] = new BasicToken(rank, false);
	}
	else {
		board[ADJ_COORD(pos.x)][ADJ_COORD(pos.y)] = new BasicToken(rank, true);
	}	
}

GameBoard::~GameBoard()
{
}
