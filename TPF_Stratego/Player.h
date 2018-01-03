#pragma once
#include "MarshalToken.h"
#include "GameBoard.h"
#include <vector>

typedef int MoveResult;
enum MoveTypes {MOVE_VALID = 1, MOVE_NOT_VALID, RESELECT, ATTACK_TRY};

typedef int State;
enum BasicStates{LOCAL_MOVE = 1, ENEMY_MOVE, WAIT_FOR_RANGE};

class Player
{
public:
	Player(PlayerType color);
	MoveResult move_local_token(PosType src_pos, PosType dst_pos); /// Retorna MoveTypes
	void process_local_attack(PosType src_pos, PosType dst_pos, RangeType attacked_token_range); /// Recibe el rango atacado y procesa el ataque												
	MoveResult move_enemy_token(PosType src_pos, PosType dst_pos);
	~Player();
	GameBoard local_board;
private:
	PlayerType player;
	State game_state;
	vector <RangeType> tokens_lost;
};

