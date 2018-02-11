#include "stdafx.h"
#include "ColonelToken.h"


ColonelToken::ColonelToken(PlayerType owner) : BasicToken(COLONEL, true, owner)
{
}

bool ColonelToken::validate_movement(PosType src_pos,PosType dst_pos)
{
	if (src_pos.i == dst_pos.i) {
		if (((src_pos.j + 1) == dst_pos.j) || ((src_pos.j - 1) == dst_pos.j)) {
			return true; /// Valido OK
		}
		else {
			return false; /// Movimiento invalido
		}
	}
	else if (src_pos.j == dst_pos.j) {
		if (((src_pos.i + 1) == dst_pos.i) || ((src_pos.i - 1) == dst_pos.i)) {
			return true; /// Valido OK
		}
		else {
			return false; /// Movimiento invalido
		}
	}
	else {
		return false; /// Movimiento invalido
	}
}

AttackResult ColonelToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return LOSE;
	}
	if (enemy_range < COLONEL) {
		return LOSE;
	}
	if (enemy_range == COLONEL) {
		return NOBODY_WON;
	}
	if ((enemy_range > COLONEL) && (enemy_range < BOMB)) {
		return WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}


ColonelToken::~ColonelToken()
{
}
