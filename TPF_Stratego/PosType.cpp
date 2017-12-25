#include "stdafx.h"
#include "PosType.h"


PosType::PosType()
{
	/// Default create setting
	x = 'A';
	y = '1';
}

PosType PosType::get_token_pos()
{
	PosType temp;
	temp.set_token_pos(this->x, this->y);
	return temp;
}

void PosType::set_token_pos(unsigned char new_x, unsigned new_y)
{
	x = new_x;
	y = new_y;
}


PosType::~PosType()
{
}
