#pragma once
#include "PosType.h"

enum Ranges {MARSHAL=1, GENERAL, COLONEL, MAJOR, CAPTAIN, LIEUTENANT, SERGEANT, MINER, SCOUT, SPY,
				BOMB, FLAG};

enum Players {RED=1, BLUE};

typedef unsigned int RangeType;
typedef unsigned int PlayerType;

class BasicToken // Se hereda a cada token particular
{
public:
	BasicToken(RangeType set_range, bool move_en, PlayerType player);
	PosType get_token_pos();
	void set_token_pos(unsigned char new_x, unsigned new_y);
	RangeType get_range();
	bool is_move_enabled();
	PlayerType get_player();
	~BasicToken();
private:
	PosType curr_pos; /// Posicion actual
	RangeType range; /// Rango del token
	bool move_enable; /// Es "false" cuando el token NO es jugable (Bomb - Flag), sino "true"
	PlayerType player_owner; /// {1 = RED - 2 = BLUE}
};

