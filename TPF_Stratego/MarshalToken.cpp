#include "stdafx.h"
#include "MarshalToken.h"
#include <iostream>

MarshalToken::MarshalToken() : BasicToken(MARSHAL, true)
{
}

bool MarshalToken::validate_movement(PosType dst_pos)
{
	PosType src_pos = this->get_token_pos();

	if (src_pos.x == dst_pos.x) {
		if (((src_pos.y + 1) == dst_pos.y) || ((src_pos.y - 1) == dst_pos.y)) {
			return true; /// Valido OK
		}
		else {
			return false; /// Movimiento invalido
		}
	}
	else if (src_pos.y == dst_pos.y) {
		if (((src_pos.x + 1) == dst_pos.x) || ((src_pos.x - 1) == dst_pos.x)) {
			return true; /// Valido OK
		}
		else {
			return false; /// Movimiento invalido
		}
	}
	else {
		return false; /// Movimiento invalido
	}
}

void MarshalToken::move(PosType dst_pos, BasicToken** board_ref)
{
	PosType src = this->get_token_pos();
	(&(board_ref[ADJ_COORD(dst_pos.x)]))[ADJ_COORD(dst_pos.y)] = (&(board_ref[ADJ_COORD(src.x)]))[ADJ_COORD(src.y)];
	///(&(board_ref[ADJ_COORD(src.x)]))[ADJ_COORD(src.y)] = nullptr;
	(&(board_ref[ADJ_COORD(src.x)]))[ADJ_COORD(src.y)] = nullptr;
	this->set_token_pos(dst_pos.x, dst_pos.y);
}

AttackResult MarshalToken::attack(RangeType enemy_range)
{
	if (enemy_range == MARSHAL)
		return NOBODY_WON;

	else {
		return WON;
	}
}

MarshalToken::~MarshalToken()
{
}
