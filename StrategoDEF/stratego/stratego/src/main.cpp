#include <Framework/sysgame/sysgame.h>
#include <game/controller/menu_test/menu_test.h>

int main() {
	Sysgame sys("resource/game_config.xml");
	
	sys.setNewController( (Controller*)new menuTest(&sys));

	while (1) {
		sys.update();
	}
}