#include "stdafx.h"
#include "BombToken.h"


BombToken::BombToken(PlayerType owner) : BasicToken(BOMB, false, owner)
{
}

AttackResult BombToken::attack(RangeType enemy_range)
{
	if (enemy_range == MINER) {
		return LOSE;
	}
	else {
		return WON;
	}
}


BombToken::~BombToken()
{
}
