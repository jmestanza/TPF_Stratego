#pragma once
#include "MarshalToken.h"
#include "GameBoard.h"

typedef int LocalMove;
typedef int EnemyMove;
enum MoveTypes {};

typedef int GameState;
enum States { LOCAL_MOVE = 1, SERVER_MOVE, WAIT_SERVER_TOKENRANGE};

class Player
{
public:
	Player();
	LocalMove move_local_token(PosType src_pos, PosType dst_pos); /// 
	EnemyMove move_enemy_token(PosType src_pos, PosType dst_pos);
	~Player();
	GameBoard local_board;
private:
	GameState state;
};

