#pragma once

#include "BasicToken.h"


//// ficha desconocida presente en el tablero
class UnknownToken : public BasicToken {
	public:
		UnknownToken(PlayerType owner);
		int attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
		~UnknownToken();
};