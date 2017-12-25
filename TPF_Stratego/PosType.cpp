#include "stdafx.h"
#include "PosType.h"


PosType::PosType()
{
}

PosType PosType::get_token_pos()
{
	PosType temp;
	temp.set_token_pos(this->col, this->row);
	return temp;
}

void PosType::set_token_pos(unsigned char new_col, unsigned new_row)
{
	col = new_col;
	row = new_row;
}


PosType::~PosType()
{
}
