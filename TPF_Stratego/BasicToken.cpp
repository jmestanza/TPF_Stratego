#include "stdafx.h"
#include "BasicToken.h"

BasicToken::BasicToken(RangeType set_range, bool move_en)
{
	range = set_range;
	move_enable = move_en;
}

PosType BasicToken::get_token_pos()
{
	PosType temp;
	temp.x = this->curr_pos.x;
	temp.y = this->curr_pos.y;
	return temp;
}

void BasicToken::set_token_pos(unsigned char new_x, unsigned new_y)
{
	this->curr_pos.x = new_x;
	this->curr_pos.y = new_y;
}

RangeType BasicToken::get_range()
{
	return range;
}

bool BasicToken::is_move_enabled()
{
	return move_enable;
}


BasicToken::~BasicToken()
{
}
