#pragma once
#include "BasicToken.h"

class LieutenantToken : public BasicToken
{
public:
	LieutenantToken(PlayerType owner);
	bool validate_movement(PosType src_pos,PosType dst_pos); /// Valida el movimiento a realizar solo por su trayectoria
	AttackResult attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
	~LieutenantToken();
};

