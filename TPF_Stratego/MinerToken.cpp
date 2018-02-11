#include "stdafx.h"
#include "MinerToken.h"


MinerToken::MinerToken(PlayerType owner) : BasicToken(MINER, true, owner)
{
}

bool MinerToken::validate_movement(PosType src_pos,PosType dst_pos)
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

AttackResult MinerToken::attack(RangeType enemy_range)
{
	if (enemy_range == BOMB) {
		return WON; /// El minero desactiva las bombas
	}
	if (enemy_range < MINER) {
		return LOSE;
	}
	if (enemy_range == MINER) {
		return NOBODY_WON;
	}
	if ((enemy_range > MINER) && (enemy_range != FLAG)) {
		return WON;
	}
	if (enemy_range == FLAG) {
		return GAME_WON;
	}
}


MinerToken::~MinerToken()
{
}
