#include <stdio.h>
#include <tchar.h>
#include "FlagToken.h"


FlagToken::FlagToken(PlayerType owner) : BasicToken(FLAG, false, owner)
{
}


FlagToken::~FlagToken()
{
}
