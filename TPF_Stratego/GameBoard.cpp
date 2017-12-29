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

void GameBoard::set_tile(PosType token_pos, BasicToken * token)
{
	PosType temp = token->get_token_pos();
	board[ADJ_COORD(token_pos.x)][ADJ_COORD(token_pos.y)] = token;
}

GameBoard::~GameBoard()
{
}
