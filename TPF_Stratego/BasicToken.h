#pragma once
#include "PosType.h"

using namespace std;

enum Ranges {ENEMY = 0, MARSHAL, GENERAL, COLONEL, MAJOR, CAPTAIN, LIEUTENANT, SERGEANT, MINER, SCOUT, 
			 SPY, BOMB, FLAG};
#define INVALID_RANGE -1

enum Players {RED=1, BLUE};

typedef unsigned int RangeType;
typedef unsigned int PlayerType;

typedef int AttackResult;
#define GAME_WON 2
#define WON 1
#define NOBODY_WON 0
#define LOSE -1

#define POS_MASK 0x0F
#define ADJ_COORD(a) ((a&POS_MASK)-1) /// Ajusta coordenada del tablero a indice de matriz

class BasicToken // Se hereda a cada token particular
{
public:
	BasicToken(RangeType set_range, bool move_en, PlayerType player);
	PosType get_token_pos();
	void set_token_pos(unsigned char new_x, unsigned char new_y);
	RangeType get_range();
	PlayerType get_player();
	bool is_move_enabled();
	~BasicToken();
private:
	PosType curr_pos; /// Posicion actual
	RangeType range; /// Rango del token
	bool move_enable; /// Es "false" cuando el token NO es jugable (Bomb - Flag), sino "true"
	PlayerType player_owner; /// Jugador al que pertenece la ficha
};

