#include <stdio.h>
#include <tchar.h>
#include "MarshalToken.h"
#include <iostream>

MarshalToken::MarshalToken(PlayerType owner) : BasicToken(MARSHAL, true, owner)
{
}

bool MarshalToken::validate_movement(PosType src_pos,PosType dst_pos)
{
	//PosType src_pos = this->get_token_pos();

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

AttackResult MarshalToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return LOSE;
	}
	else if (enemy_range == MARSHAL) {
		return NOBODY_WON;
	}
	else if(enemy_range == FLAG) {
		return GAME_WON;
	}
	else {
		return WON;
	}
}

MarshalToken::~MarshalToken()
{
}
