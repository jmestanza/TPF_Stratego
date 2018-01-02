#pragma once
#include "MarshalToken.h"
#include "GameBoard.h"

typedef int LocalMove;
typedef int EnemyMove;
enum MoveTypes {MOVE_VALID = 1, MOVE_NOT_VALID, RESELECT, ATTACK_TRY};

typedef int GameState;
enum BasicStates{LOCAL_MOVE = 1, ENEMY_MOVE, WAIT_FOR_RANGE};

class Player
{
public:
	Player(PlayerType color);
	LocalMove move_local_token(PosType src_pos, PosType dst_pos); /// Retorna MoveTypes
	void process_local_attack(PosType src_pos, PosType dst_pos, RangeType attacked_token_range); /// Recibe el rango atacado y procesa el ataque												
	EnemyMove move_enemy_token(PosType src_pos, PosType dst_pos);
	~Player();
	GameBoard local_board;
private:
	PlayerType player;
	GameState basic_state;
};

