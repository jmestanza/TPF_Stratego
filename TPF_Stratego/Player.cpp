#include "stdafx.h"
#include "Player.h"


Player::Player(PlayerType color)
{
	player = color;

	if (color == RED) {
		game_state = LOCAL_MOVE;
		local_board.set_enemy_tokens(BLUE);
	}
	else {
		game_state = ENEMY_MOVE;
		local_board.set_enemy_tokens(RED);
	}
}

MoveResult Player::move_local_token(PosType src_pos, PosType dst_pos)
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

	if (!(token->is_move_enabled())) {
		return MOVE_NOT_VALID; /// No es una ficha movible
	}

	RangeType local_range = token->get_range();
	bool move_valid = false;

	switch (local_range) /// Validacion del movimiento - cada ficha puede moverse distinto
	{
	case MARSHAL:
		move_valid = ((MarshalToken*)token)->validate_movement(dst_pos);
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

	if (move_valid) {
		if (dst_tile == nullptr) {
			local_board.move_token(src_pos, dst_pos);
			game_state = ENEMY_MOVE;
			return MOVE_VALID; /// Movimiento normal
		}
		else {
			game_state = WAIT_FOR_RANGE;
			return ATTACK_TRY; /// Ataque al enemigo
		}
	}
	else {
		return MOVE_NOT_VALID; /// Movimiento no valido para la ficha elegida
	}
}

void Player::process_attack(PosType src_pos, PosType dst_pos, RangeType attack_token_range)
{
	BasicToken* token = local_board.get_tile(src_pos);
	AttackResult res;

	switch (token->get_range())
	{
	case MARSHAL:
		res = ((MarshalToken*)token)->attack(attack_token_range);
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
		tokens_lost.push_back(token->get_range()); /// Añade a fichas perdidas
		local_board.clear_tile(src_pos);
		local_board.clear_tile(dst_pos);
	}
	else if (res == LOSE) {
		tokens_lost.push_back(token->get_range()); /// Añade a fichas perdidas
		local_board.clear_tile(src_pos);
	}

	if (game_state == LOCAL_MOVE) { /// Alternar turnos
		game_state = ENEMY_MOVE;
	}
	else {
		game_state = LOCAL_MOVE;
	}
}

MoveResult Player::move_enemy_token(PosType src_pos, PosType dst_pos)
{
	BasicToken* enemy_token = local_board.get_tile(src_pos);
	BasicToken* dst_title = local_board.get_tile(dst_pos);

	if (enemy_token == nullptr) {
		return ERROR; /// El dato NO es valido - Error de comunicaion
	}

	if (enemy_token->get_player() == player) {
		return ERROR; /// El dato NO es valido - Error de comunicaion
	}

	if (dst_title->get_player() != player) {
		return ERROR; /// El dato NO es valido - Error de comunicaion
	}

	if (dst_title == nullptr) {
		local_board.move_token(src_pos, dst_pos);
		game_state = LOCAL_MOVE;
		return MOVE_VALID; /// Movimiento normal
	}
	else {
		game_state = WAIT_FOR_RANGE;
		return ATTACK_TRY; /// Ataque del enemigo
	}
}

State Player::get_game_state()
{
	return game_state;
}

Player::~Player()
{
}
