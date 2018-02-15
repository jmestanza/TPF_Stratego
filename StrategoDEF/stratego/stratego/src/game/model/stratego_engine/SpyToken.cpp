#include <stdio.h>
#include <tchar.h>
#include "SpyToken.h"


SpyToken::SpyToken(PlayerType owner) : BasicToken(SPY, true, owner)
{
}

bool SpyToken::validate_movement(PosType src_pos,PosType dst_pos)
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
