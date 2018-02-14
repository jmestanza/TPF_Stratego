#include <iostream>
#include <framework/sysgame/sysgame.h>
#include <game/controller/menu_test/menu_test.h>
#include <game/controller/showTimeTest/showTimeTest.h>
#include <game/controller/gameArea/gameArea.h>

using namespace std;

int main() {

	//cout << "hello world \n";

	try{
		Sysgame sys;
		sys.setNewController( (Controller*)new gameArea(&sys,"ariel","joaquin",1));
		
		while (!sys.quit()) sys.update();
		
	} catch (exception &e) {
		cerr << "A fatal error occurred and the program needed to stop \n";
		cerr << "Reason: " << e.what() << '\n';
		getchar();
	}
}