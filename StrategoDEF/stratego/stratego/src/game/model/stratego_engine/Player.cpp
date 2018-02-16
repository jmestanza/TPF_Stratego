#include <stdio.h>
#include <tchar.h>
#include "Player.h"
#include <iostream>
using namespace std;

void printTable(tablero_t& tablero) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (tablero[i][j] == nullptr) {
				cout << "N";
			}
			else {
				cout << tablero[i][j]->get_range();
				//cout << tablero[i][j]->get_player();
			}
		}	cout << endl;
	}
}

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
	
	// si pasa todo esto es porque es valido -> debe ser null el destiny
	if(dst_tile != nullptr)
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
		move_valid = ((MarshalToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case GENERAL:
		move_valid = ((GeneralToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case COLONEL:
		move_valid = ((ColonelToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case MAJOR:
		move_valid = ((MajorToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case CAPTAIN:
		move_valid = ((CaptainToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case LIEUTENANT:
		move_valid = ((LieutenantToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case SERGEANT:
		move_valid = ((SergeantToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case MINER:
		move_valid = ((MinerToken*)token)->validate_movement(src_pos,dst_pos);
		break;
	case SCOUT:
		move_valid = ((ScoutToken*)token)->validate_movement(src_pos,dst_pos, local_board.get_board());
		break;
	case SPY:
		move_valid = ((SpyToken*)token)->validate_movement(src_pos,dst_pos);
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
		res = ((GeneralToken*)token)->attack(attack_token_range);
		break;
	case COLONEL:
		res = ((ColonelToken*)token)->attack(attack_token_range);
		break;
	case MAJOR:
		res = ((MajorToken*)token)->attack(attack_token_range);
		break;
	case CAPTAIN:
		res = ((CaptainToken*)token)->attack(attack_token_range);
		break;
	case LIEUTENANT:
		res = ((LieutenantToken*)token)->attack(attack_token_range);
		break;
	case SERGEANT:
		res = ((SergeantToken*)token)->attack(attack_token_range);
		break;
	case MINER:
		res = ((MinerToken*)token)->attack(attack_token_range);
		break;
	case SCOUT:
		res = ((ScoutToken*)token)->attack(attack_token_range);
		break;
	case SPY:
		res = ((SpyToken*)token)->attack(attack_token_range);
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
	if(game_state == ENEMY_MOVE) {
		game_state = LOCAL_MOVE;
	}
}

MoveResult Player::move_enemy_token(PosType src_pos, PosType dst_pos)
{
	BasicToken* enemy_token = local_board.get_tile(src_pos);
	BasicToken* dst_title = local_board.get_tile(dst_pos);

	if (enemy_token == nullptr) {
		return ERRORV; /// El dato NO es valido - Error de comunicaion
	}

	if (enemy_token->get_player() == player) {
		return ERRORV; /// El dato NO es valido - Error de comunicaion
	}

	if (dst_title == nullptr) {
		local_board.move_token(src_pos,dst_pos);
		game_state = LOCAL_MOVE;
		return MOVE_VALID; /// Movimiento normal
	} else {
		game_state = WAIT_FOR_RANGE;
		return ATTACK_TRY; /// Ataque del enemigo
	}

	if (dst_title->get_player() != player) {
		return ERRORV; /// El dato NO es valido - Error de comunicaion
	}

}

State Player::get_game_state()
{
	return game_state;
}

PlayerType Player::get_player() {
	return player;
}

void Player::set_game_state(State st) {
	this->game_state = st;
}

Player::~Player()
{
}
