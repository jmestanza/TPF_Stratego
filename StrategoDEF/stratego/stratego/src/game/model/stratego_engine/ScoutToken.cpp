#include <stdio.h>
#include <tchar.h>
#include "ScoutToken.h"


ScoutToken::ScoutToken(PlayerType owner) : BasicToken(SCOUT, true, owner)
{
}

bool ScoutToken::validate_movement(PosType src_pos,PosType dst_pos, tablero_t& board_ref)
{
	bool tile_empty = true;
	int deltax,deltay;
	dst_pos.i-src_pos.i>0? deltax= dst_pos.i - src_pos.i :deltax= src_pos.i - dst_pos.i;
	dst_pos.j - src_pos.j>0 ? deltay = dst_pos.j - src_pos.j : deltay = src_pos.j - dst_pos.j;

	if(deltax>1 || deltay>1){
		if (board_ref[dst_pos.i][dst_pos.j] != nullptr) {
			tile_empty =false;
		}
	}
	if (src_pos.i == dst_pos.i) {
		if (dst_pos.j > src_pos.j ){
			for (int j = ((src_pos.j) + 1); j < ((dst_pos.j) - 1); j++) {
				if (board_ref[(src_pos.i)][j] != nullptr) {
					tile_empty = false;
				}
			}
		} else if (dst_pos.j < src_pos.j) {
			for (int j = ((dst_pos.j) + 1); j < ((src_pos.j) - 1); j++) {
				if (board_ref[(src_pos.i)][j] != nullptr) {
					tile_empty = false;
				}
			}
		}

		if (!tile_empty) {
			return false; /// Movimiento invalido - NO se puede saltar sobre fichas
		}
	} else if (src_pos.j == dst_pos.j) {
		if (dst_pos.i > src_pos.i) {
			for (int i = ((src_pos.i) + 1); i < ((dst_pos.i) - 1); i++) {
				if (board_ref[i][(src_pos.j)] != nullptr) {
					tile_empty = false;
				}
			}
		} else if (dst_pos.i < src_pos.i) {
			for (int i = ((dst_pos.i) + 1); i < ((src_pos.i) - 1); i++) {
				if (board_ref[i][(src_pos.j)] != nullptr) {
					tile_empty = false;
				}
			}
		}
	
		if (!tile_empty) {
			return false; /// Movimiento invalido - NO se puede saltar sobre fichas
		}
	} else {
		return false; /// Movimiento invalido
	}
	return true;
}


AttackResult ScoutToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return LOSE;
	}
	if (enemy_range < SCOUT) {
		return LOSE;
	}
	if (enemy_range == SCOUT) {
		return NOBODY_WON;
	}
	if ((enemy_range > SCOUT) && (enemy_range < BOMB)) {
		return WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}

ScoutToken::~ScoutToken()
{
}
