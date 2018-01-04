#pragma once
#include "BasicToken.h"

class ScoutToken : public BasicToken
{
public:
	ScoutToken(PlayerType owner);
	bool validate_movement(PosType dst_pos, BasicToken** board_ref); /// Valida el movimiento a realizar solo por su trayectoria
	AttackResult attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
	~ScoutToken();
};

