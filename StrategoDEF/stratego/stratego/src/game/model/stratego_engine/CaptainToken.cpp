#include <stdio.h>
#include <tchar.h>
#include "CaptainToken.h"


CaptainToken::CaptainToken(PlayerType owner) : BasicToken(CAPTAIN, true, owner)
{
}

bool CaptainToken::validate_movement(PosType src_pos,PosType dst_pos)
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

AttackResult CaptainToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return LOSE;
	}
	if (enemy_range < CAPTAIN) {
		return LOSE;
	}
	if (enemy_range == CAPTAIN) {
		return NOBODY_WON;
	}
	if ((enemy_range > CAPTAIN) && (enemy_range < BOMB)) {
		return WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}


CaptainToken::~CaptainToken()
{
}
