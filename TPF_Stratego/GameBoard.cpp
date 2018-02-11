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
	return board[(tile.i)][(tile.j)];
}

void GameBoard::set_new_token(PlayerType owner, PosType pos, RangeType rank)
{	
	//if(this->board)
	if ((rank == FLAG) || (rank == BOMB)) {
		board[pos.i][pos.j] = new BasicToken(rank, false, owner);
	}
	else {
		board[pos.i][pos.j] = new BasicToken(rank, true, owner);
	}	
}

void GameBoard::set_enemy_tokens(PlayerType enemy_color)
{
	if (enemy_color == RED) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = new BasicToken(ENEMY, false, RED);
			}
		}
	}
	else {
		for (int i = 6; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = new BasicToken(ENEMY, false, BLUE);
			}
		}
	}
}

void GameBoard::clear_tile(PosType tile_pos)
{
	if(board[tile_pos.i][tile_pos.j] != nullptr)
	delete board[tile_pos.i][tile_pos.j];
	//revisar si no hay memory leak
}

void GameBoard::move_token(PosType src_pos, PosType dst_pos)
{
	board[dst_pos.i][dst_pos.j] = board[src_pos.i][src_pos.j];
	board[dst_pos.i][dst_pos.j]->set_token_pos(dst_pos.i, dst_pos.j);
	board[src_pos.i][src_pos.j] = nullptr;
}

GameBoard::~GameBoard()
{
}
