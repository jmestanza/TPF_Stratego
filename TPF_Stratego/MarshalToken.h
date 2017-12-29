#pragma once
#include "BasicToken.h"

class MarshalToken : public BasicToken
{
public:
	MarshalToken();
	bool validate_movement(PosType dst_pos); /// Return {true - Valido, false - NO valido}
	void move(PosType dst_pos, BasicToken** board_ref); /// Mueve la pieza asumiendo valido el movimiento
	AttackResult attack(RangeType enemy_range); /// Returns {-1 Perdio, 0 Empate, 1 Gano}
	~MarshalToken();
};

