#include "stdafx.h"
#include "SpyToken.h"


SpyToken::SpyToken(PlayerType owner) : BasicToken(SPY, true, owner)
{
}

bool SpyToken::validate_movement(PosType dst_pos)
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

AttackResult SpyToken::attack(RangeType enemy_range)
{
	if (enemy_range == MARSHAL) {
		return WON; /// El espia gana al Marshal
	}
	if ((enemy_range < SPY)&&(enemy_range != MARSHAL)) {
		return LOSE;
	}
	if (enemy_range == SPY) {
		return NOBODY_WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}


SpyToken::~SpyToken()
{
}
