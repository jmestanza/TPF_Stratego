#pragma once
#include "BasicToken.h"

class BombToken : public BasicToken{
	public:
		BombToken(PlayerType owner);
		int attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
		~BombToken();
};

