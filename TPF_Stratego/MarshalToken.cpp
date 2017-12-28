#include "stdafx.h"
#include "MarshalToken.h"


MarshalToken::MarshalToken() : BasicToken(MARSHAL, true)
{
}


AttackType MarshalToken::attack(RangeType enemy_range)
{
	return 1; /// Marshal siempre gana al atacar
}

MarshalToken::~MarshalToken()
{
}
