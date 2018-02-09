#include "stdafx.h"
#include "ScoutToken.h"


ScoutToken::ScoutToken(PlayerType owner) : BasicToken(SCOUT, true, owner)
{
}

bool ScoutToken::validate_movement(PosType dst_pos, tablero_t& board_ref)
{
	PosType src_pos = this->get_token_pos();
	int delta_x;
	((dst_pos.x - src_pos.x) > 0) ? delta_x = dst_pos.x - src_pos.x : delta_x = src_pos.x - dst_pos.x;
	int delta_y;
	((dst_pos.y - src_pos.y) > 0) ? delta_y = dst_pos.y - src_pos.y : delta_y = src_pos.y - dst_pos.y;
	bool tile_empty = true;

	if (src_pos.x == dst_pos.x) {
		if (dst_pos.y > src_pos.y) {
			for (int j = ((src_pos.y) + 1); j < ((dst_pos.y) - 1); j++) {
				if (board_ref[(src_pos.x)][j] != nullptr) {
					tile_empty = false;
				}
			}
		}
		else if (dst_pos.y < src_pos.y) {
			for (int j = ((dst_pos.y) + 1); j < ((src_pos.y) - 1); j++) {
				if (board_ref[(src_pos.x)][j] != nullptr) {
					tile_empty = false;
				}
			}
		}

		if (!tile_empty) {
			return false; /// Movimiento invalido - NO se puede saltar sobre fichas
		}
		else {
			if ((board_ref[(dst_pos.x)][dst_pos.y] != nullptr) && (delta_y > 1)) {
				return false; /// Movimiento invalido - SOLO se puede atacar si estan en casilleros contiguos
			}
			else {
				return true;
			}
		}
	}
	else if (src_pos.y == dst_pos.y) {
		if (dst_pos.x > src_pos.x) {
			for (int i = ((src_pos.x) + 1); i < ((dst_pos.x) - 1); i++) {
				if (board_ref[i][(src_pos.y)] != nullptr) {
					tile_empty = false;
				}
			}
		}
		else if (dst_pos.x < src_pos.x) {
			for (int i = ((dst_pos.x) + 1); i < ((src_pos.x) - 1); i++) {
				if (board_ref[i][(src_pos.y)] != nullptr) {
					tile_empty = false;
				}
			}
		}

		if (!tile_empty) {
			return false; /// Movimiento invalido - NO se puede saltar sobre fichas
		}
		else {
			if ((board_ref[(dst_pos.x)][dst_pos.y] != nullptr) && (delta_x > 1)) {
				return false; /// Movimiento invalido - SOLO se puede atacar si estan en casilleros contiguos
			}
			else {
				return true;
			}
		}
	}
	else {
		return false; /// Movimiento invalido
	}
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
