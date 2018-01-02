#include "stdafx.h"
#include "Player.h"


Player::Player(PlayerType color)
{
	player = color;
}

LocalMove Player::move_local_token(PosType src_pos, PosType dst_pos)
{
	BasicToken* token = local_board.get_tile(src_pos);
	BasicToken* dst_tile = local_board.get_tile(dst_pos);

	if (token == nullptr) {
		return MOVE_NOT_VALID; /// El casillero esta vacio!
	}

	if (token->get_player() != player) {
		return MOVE_NOT_VALID; /// No es una ficha propia
	}

	if (dst_tile->get_player() == player) {
		return RESELECT; /// El tile de destino es otra ficha propia
	}

	if (!token->is_move_enabled()) {
		return MOVE_NOT_VALID; /// No es una ficha movible
	}

	RangeType temp_range = token->get_range();
	bool move_valid = false;

	switch (temp_range)
	{
	case MARSHAL:
		move_valid = ((MarshalToken*)token)->validate_movement(dst_pos);
		if (move_valid) {
			if (dst_tile == nullptr) {
				((MarshalToken*)token)->move(dst_pos, local_board.get_board());
				basic_state = ENEMY_MOVE;
				return MOVE_VALID; /// Movimiento normal
			}
			else {
				basic_state = WAIT_FOR_RANGE;
				return ATTACK_TRY; /// Ataque al enemigo
			}
		}
		else {
			return MOVE_NOT_VALID; /// Movimiento no valido para la ficha elegida
		}
		break;
	case GENERAL:
		break;
	case COLONEL:
		break;
	case MAJOR:
		break;
	case CAPTAIN:
		break;
	case LIEUTENANT:
		break;
	case SERGEANT:
		break;
	case MINER:
		break;
	case SCOUT:
		break;
	case SPY:
		break;
	}
}

void Player::process_local_attack(PosType src_pos, PosType dst_pos, RangeType attacked_token_range)
{
	BasicToken* token = local_board.get_tile(src_pos);
	RangeType temp_range = token->get_range();
	AttackResult res;

	switch (temp_range)
	{
	case MARSHAL:
		res = ((MarshalToken*)token)->attack(attacked_token_range);
		break;
	case GENERAL:
		break;
	case COLONEL:
		break;
	case MAJOR:
		break;
	case CAPTAIN:
		break;
	case LIEUTENANT:
		break;
	case SERGEANT:
		break;
	case MINER:
		break;
	case SCOUT:
		break;
	case SPY:
		break;
	}

	if (res == WON) {
		local_board.move_token(src_pos, dst_pos);
	}
	else if (res == NOBODY_WON) {
		local_board.clear_tile(src_pos);
		local_board.clear_tile(dst_pos);
	}
	else if (res == LOSE) {
		/// ???
	}
}

//enum Ranges {
//	ENEMY = 0, MARSHAL, GENERAL, COLONEL, MAJOR, CAPTAIN, LIEUTENANT, SERGEANT, MINER, SCOUT, SPY,
//	BOMB, FLAG
//};

Player::~Player()
{
}
