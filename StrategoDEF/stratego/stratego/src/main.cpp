#include <Framework/sysgame/sysgame.h>
#include <game/controller/menu_test/menu_test.h>

int main() {

	cout << "hello world \n";

	Sysgame sys("resource/game_config.xml");
	
	sys.setNewController( (Controller*)new menuTest(&sys));

	while (!sys.quit()) sys.update();
	
}