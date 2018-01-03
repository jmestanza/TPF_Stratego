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

BasicToken * GameBoard::get_tile(PosType tile)
{
	return board[ADJ_COORD(tile.x)][ADJ_COORD(tile.y)];
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

void GameBoard::set_enemy_tokens(PlayerType enemy_color)
{
	if (enemy_color == BLUE) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < 4; j++) {
				board[i][j] = new BasicToken(ENEMY, false, BLUE);
			}
		}
	}
	else {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 6; j < BOARD_SIZE; j++) {
				board[i][j] = new BasicToken(ENEMY, false, RED);
			}
		}
	}
}

void GameBoard::clear_tile(PosType tile_pos)
{
	board[ADJ_COORD(tile_pos.x)][ADJ_COORD(tile_pos.y)] = nullptr;
}

void GameBoard::move_token(PosType src_pos, PosType dst_pos)
{
	board[ADJ_COORD(dst_pos.x)][ADJ_COORD(dst_pos.y)] = board[ADJ_COORD(src_pos.x)][ADJ_COORD(src_pos.y)];
	board[ADJ_COORD(dst_pos.x)][ADJ_COORD(dst_pos.y)]->set_token_pos(dst_pos.x, dst_pos.y);
	board[ADJ_COORD(src_pos.x)][ADJ_COORD(src_pos.y)] = nullptr;
}

GameBoard::~GameBoard()
{
}
