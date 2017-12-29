#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard()
{
}

BasicToken ** GameBoard::get_board()
{
	return board[0];
}

void GameBoard::set_tile(BasicToken * token)
{
	PosType temp = token->get_token_pos();
	board[ADJ_COORD(temp.x)][ADJ_COORD(temp.y)] = token;
}

GameBoard::~GameBoard()
{
}
