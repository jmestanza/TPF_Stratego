#pragma once
#include "BasicToken.h"

class marshal_token : public BasicToken
{
public:
	marshal_token();
	bool move(PosType dest_pos);
	int attack();
	~marshal_token();
};

