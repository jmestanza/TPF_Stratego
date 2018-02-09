#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		board.push_back(vector<BasicToken*>(BOARD_SIZE,nullptr));
	}
}

tablero_t& GameBoard::get_board()
{
	return board;
}


BasicToken * GameBoard::get_tile(PosType tile)
{
	return board[(tile.x)][(tile.y)];
}

void GameBoard::set_new_token(PlayerType owner, PosType pos, RangeType rank)
{	
	//if(this->board)
	if ((rank == FLAG) || (rank == BOMB)) {
		board[pos.x][pos.y] = new BasicToken(rank, false, owner);
	}
	else {
		board[pos.x][pos.y] = new BasicToken(rank, true, owner);
	}	
}

void GameBoard::set_enemy_tokens(PlayerType enemy_color)
{
	if (enemy_color != BLUE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = new BasicToken(ENEMY, false, BLUE);
			}
		}
	}
	else {
		for (int i = 6; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = new BasicToken(ENEMY, false, RED);
			}
		}
	}
}

void GameBoard::clear_tile(PosType tile_pos)
{
	delete board[(tile_pos.x)][(tile_pos.y)];
}

void GameBoard::move_token(PosType src_pos, PosType dst_pos)
{
	board[(dst_pos.x)][(dst_pos.y)] = board[(src_pos.x)][(src_pos.y)];
	board[(dst_pos.x)][(dst_pos.y)]->set_token_pos(dst_pos.x, dst_pos.y);
	board[(src_pos.x)][(src_pos.y)] = nullptr;
}

GameBoard::~GameBoard()
{
}
