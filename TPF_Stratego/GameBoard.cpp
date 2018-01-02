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

void GameBoard::set_new_token(PlayerType owner, PosType pos, RangeType rank)
{
	if ((rank == FLAG) || (rank == BOMB)) {
		board[ADJ_COORD(pos.x)][ADJ_COORD(pos.y)] = new BasicToken(rank, false, owner);
	}
	else {
		board[ADJ_COORD(pos.x)][ADJ_COORD(pos.y)] = new BasicToken(rank, true, owner);
	}	
}

void GameBoard::move_token(PosType src_pos, PosType dst_pos)
{
	board[ADJ_COORD(dst_pos.x)][ADJ_COORD(dst_pos.y)] = board[ADJ_COORD(src_pos.x)][ADJ_COORD(src_pos.y)];
	board[ADJ_COORD(src_pos.x)][ADJ_COORD(src_pos.y)] = nullptr;
}

RangeType GameBoard::get_token_range(PosType token_pos)
{
	return board[ADJ_COORD(token_pos.x)][ADJ_COORD(token_pos.y)]->get_range();
}

GameBoard::~GameBoard()
{
}
