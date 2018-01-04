#pragma once
#include "BasicToken.h"

class CaptainToken : public BasicToken
{
public:
	CaptainToken(PlayerType owner);
	bool validate_movement(PosType dst_pos); /// Valida el movimiento a realizar solo por su trayectoria
	AttackResult attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
	~CaptainToken();
};
