#pragma once
#include "MarshalToken.h"
#include "GeneralToken.h"
#include "ColonelToken.h"
#include "MajorToken.h"
#include "CaptainToken.h"
#include "LieutenantToken.h"
#include "SergeantToken.h"
#include "MinerToken.h"
#include "ScoutToken.h"
#include "SpyToken.h"

#include "GameBoard.h"
#include <vector>

typedef int MoveResult;
enum MoveTypes {MOVE_VALID = 1, MOVE_NOT_VALID, RESELECT, ATTACK_TRY, ERROR};

typedef int State;
enum BasicStates{LOCAL_MOVE = 1, ENEMY_MOVE, WAIT_FOR_RANGE};

class Player
{
public:
	Player(PlayerType color); /// Recibe color asignado y define quien comienza
	MoveResult move_local_token(PosType src_pos, PosType dst_pos); /// Retorna MoveTypes
	void process_attack(PosType src_pos, PosType dst_pos, RangeType attack_token_range); /// Recibe el rango atacante/atacado y resuelve											
	MoveResult move_enemy_token(PosType src_pos, PosType dst_pos); /// Retorna MoveTypes		
	State get_game_state(); /// Retorna estado actual segun BasicStates
	~Player();
	GameBoard local_board; 
private:
	PlayerType player;
	State game_state; /// Se modifica automaticamente por {move_local_token - process_attack - move_enemy_token}
	vector <RangeType> tokens_lost; /// Inicia vacio y almacena las fichas perdidas automaticamente
};

