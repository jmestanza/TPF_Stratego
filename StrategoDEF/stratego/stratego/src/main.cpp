#include <iostream>
#include <Framework/sysgame/sysgame.h>
#include <game/controller/menu_test/menu_test.h>
using namespace std;

int main() {

	//cout << "hello world \n";

	try{
		Sysgame sys;
		sys.setNewController( (Controller*)new menuTest(&sys));

		while (!sys.quit()) sys.update();
	} catch (exception &e) {
		cerr << "A fatal error occurred and the program needed to stop \n";
		cerr << "Reason: " << e.what() << '\n';
		getchar();
	}
}