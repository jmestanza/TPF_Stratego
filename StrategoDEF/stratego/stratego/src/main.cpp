/*
Funcion main: lo unico que hacemos, cargamos un sysgame, le asignamos un controller y lo hacemos correr
Avisamos si hay un error fatal
*/

#include <iostream>
#include <framework/sysgame/sysgame.h>
#include <game/controller/menu_test/menu_test.h>
#include <game/controller/showTimeTest/showTimeTest.h>
#include <game/controller/gameArea/gameArea.h>
#include <game/controller/connectMenu/connect_menu.h>

using namespace std;

int main() {

	//cout << "hello world \n";

	try {
		Sysgame sys;
		sys.setNewController((Controller*)(new ConnectMenu((Sysgame*)&sys)));

		while (!sys.quit()) sys.update();

	}
	catch (exception &e) {
		cerr << "A fatal error occurred and the program needed to stop \n";
		cerr << "Reason: " << e.what() << '\n';
		getchar();
	}
}