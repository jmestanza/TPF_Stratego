#pragma once
#include "BasicToken.h"


typedef vector<vector<BasicToken*>> tablero_t;

class ScoutToken : public BasicToken
{
public:
	ScoutToken(PlayerType owner);
	bool validate_movement(PosType src_pos,PosType dst_pos, tablero_t& board_ref); /// Valida el movimiento a realizar solo por su trayectoria
	AttackResult attack(RangeType enemy_range); /// Retorna {-1 Perdio, 0 Empate, 1 Gano}
	~ScoutToken();
};

