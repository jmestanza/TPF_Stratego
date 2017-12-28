#pragma once
#include "BasicToken.h"

typedef int AttackType;

class MarshalToken : public BasicToken
{
public:
	MarshalToken();
	bool move();
	AttackType attack(RangeType enemy_range); /// Returns {-1 Perdio, 0 Empate, 1 Gano}
	~MarshalToken();
};

