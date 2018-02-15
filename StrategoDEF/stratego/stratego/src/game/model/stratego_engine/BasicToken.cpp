#include <stdio.h>
#include <tchar.h>
#include "BasicToken.h"

int stringToRank(string code) {
	if (code == "1") return MARSHAL;
	if (code == "2") return GENERAL;
	if (code == "3") return COLONEL;
	if (code == "4") return MAJOR;
	if (code == "5") return CAPTAIN;
	if (code == "6") return LIEUTENANT;
	if (code == "7") return SERGEANT;
	if (code == "8") return MINER;
	if (code == "9") return SCOUT;
	if (code == "S") return SPY;
	if (code == "B") return BOMB;
	if (code == "F") return FLAG;
}

BasicToken::BasicToken(RangeType set_range, bool move_en, PlayerType player)
{
	range = set_range;
	move_enable = move_en;
	player_owner = player;
}

PosType BasicToken::get_token_pos()
{
	PosType temp;
	temp.i = this->curr_pos.i;
	temp.j = this->curr_pos.j;
	return temp;
}

void BasicToken::set_token_pos(unsigned char new_x, unsigned char new_y)
{
	this->curr_pos.i = new_x;
	this->curr_pos.j = new_y;
}

RangeType BasicToken::get_range()
{
	return range;
}

PlayerType BasicToken::get_player()
{
	return player_owner;
}

bool BasicToken::is_move_enabled()
{
	return move_enable;
}

BasicToken::~BasicToken()
{
}
