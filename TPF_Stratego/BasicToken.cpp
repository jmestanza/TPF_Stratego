#include "stdafx.h"
#include "BasicToken.h"

BasicToken::BasicToken(RangeType set_range, bool move_en, PlayerType player){
	range = set_range;
	move_enable = move_en;
	player_owner = player;
}

PosType BasicToken::get_token_pos(){
	PosType temp;
	temp.i = this->curr_pos.i;
	temp.j = this->curr_pos.j;
	return temp;
}

void BasicToken::set_token_pos(unsigned char new_x, unsigned char new_y){
	this->curr_pos.i = new_x;
	this->curr_pos.j = new_y;
}

RangeType BasicToken::get_range(){
	return range;
}

PlayerType BasicToken::get_player(){
	return player_owner;
}

bool BasicToken::is_move_enabled(){
	return move_enable;
}

BasicToken::~BasicToken(){
}
