#pragma once
#include "BasicToken.h"

class MarshalToken : public BasicToken
{
public:
	MarshalToken(PlayerType owner);
	bool validate_movement(PosType dst_pos); /// Valida el movimiento a realizar solo por su trayectoria, 
	                                         /// retorna {true - Valido, false - NO Valido}
	void move(PosType dst_pos, BasicToken** board_ref); /// Mueve la pieza asumiendo valido el movimiento
	AttackResult attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
	~MarshalToken();
};

