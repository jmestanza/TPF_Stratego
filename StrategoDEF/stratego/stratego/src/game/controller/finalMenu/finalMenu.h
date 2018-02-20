#pragma once
#include <game\model\stratego_engine\BasicToken.h>
#include <game\model\stratego_engine\Player.h>
#include <framework\controller\controller.h>
#include <framework\sysgame\sysgame.h>

class finalMenu {
public:
	finalMenu(Sysgame* _sys);
	~finalMenu();
private:
	Sysgame *mySys;
};

