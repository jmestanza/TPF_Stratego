#pragma once
#include "BasicToken.h"

class FlagToken : public BasicToken
{
public:
	FlagToken(PlayerType owner);
	~FlagToken();
};

