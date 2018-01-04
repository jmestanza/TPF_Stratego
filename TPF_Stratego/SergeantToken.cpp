#include "stdafx.h"
#include "SergeantToken.h"


SergeantToken::SergeantToken(PlayerType owner) : BasicToken(SERGEANT, true, owner)
{
}

bool SergeantToken::validate_movement(PosType dst_pos)
{
	PosType src_pos = this->get_token_pos();

	if (src_pos.x == dst_pos.x) {
		if (((src_pos.y + 1) == dst_pos.y) || ((src_pos.y - 1) == dst_pos.y)) {
			return true; /// Valido OK
		}
		else {
			return false; /// Movimiento invalido
		}
	}
	else if (src_pos.y == dst_pos.y) {
		if (((src_pos.x + 1) == dst_pos.x) || ((src_pos.x - 1) == dst_pos.x)) {
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

AttackResult SergeantToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return LOSE;
	}
	if (enemy_range < SERGEANT) {
		return LOSE;
	}
	if (enemy_range == SERGEANT) {
		return NOBODY_WON;
	}
	if ((enemy_range > SERGEANT) && (enemy_range < BOMB)) {
		return WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}


SergeantToken::~SergeantToken()
{
}
