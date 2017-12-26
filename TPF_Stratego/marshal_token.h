#pragma once
#include "BasicToken.h"

class marshal_token : public BasicToken
{
public:
	marshal_token();
	bool attack();
	bool move(PosType dest_pos);
	~marshal_token();
};

