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

// PLAYER - Guia general //
// --------------------- //
/// 1. Para ubicar las fichas locales al inicio, para cada una se debe usar el metodo 
///    incluido en el objeto GameBoard -> set_new_token. Las fichas enemigas se ubican 
///    por si solas segun corresponda el color con el rango ENEMY (ver en BasicToken).
/// 2. En el turno del jugador local (LOCAL_MOVE), una vez definido el movimiento se 
///    llama al metodo move_local_token con los parametros indicados, el cual lo evalua
///    y devuelve el resultado correspondiente segun MoveTypes.
/// 3. En caso de ser un movimiento normal, va a cambiar al estado ENEMY_MOVE, donde se
///    esperara a recibir el proximo paquete de movimiento enemigo, que se procesa con
///    el metodo move_enemy_token con los parametros indicados, el cual lo evalua y 
///    devuelve el resultado correspondiente segun MoveTypes.
/// 4. Con movimientos normales, 2. y 3. se repiten indefinidamente.
/// 5. Si de evaluar el movimiento en algun caso resulta un ATTACK_TRY, tanto en el caso
///    de origen local hacia el enemigo como del enemigo hacia el local, cuando ya se 
///    enviaron los paquetes ATTACK a ambos lados, se llama al metodo process_attack para
///    que lo resuelva.
///
/// !. PARA PASAJE DE POSICIONES: los parametros del tipo PosType que usan los metodos
///    son valores X e Y del tablero real, es decir de tipos char de A a J y de 1 a 10,
///    para evitar confusiones. La traduccion a indices de matriz se realiza internamente.

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
	State game_state;
	vector <RangeType> tokens_lost; /// Inicia vacio y almacena las fichas perdidas del jugador
};

