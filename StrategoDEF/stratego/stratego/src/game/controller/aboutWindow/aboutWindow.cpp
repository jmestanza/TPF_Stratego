#include "aboutWindow.h"

#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\background.h>
#include <game\controller\menu_test\menu_test.h>
#include <framework\view\utils\good_buttons.h>

AboutWindow::AboutWindow(Sysgame* sys) : Controller(sys){
}
void AboutWindow::onCreate() {

	pair<float,float> size = view->getScreenSize();
	float width = size.first,height = size.second;


	screenText *title = new screenText(mySysgame,"title");
	title->configure("Algoritmos y estructura de datos: TP final","roboto_v1",al_map_rgb(0,0,0),
		pair<float,float>(width / 2,height / 8),
		1);

	screenText *info = new screenText(mySysgame,"info");
	info->configure("Acerca de Stratego","roboto_v1",al_map_rgb(0,0,0),pair<float,float>(10,10),0);

	Background *background = new Background(mySysgame,"background");
	background->configure(
		"light_orange",
		pair<float,float>(0,0),
		mySysgame->getAllegroHandler()->getScreenSize(),
		0
	);
	vector <string> people;
	people.push_back("Joaquin Mestanza");
	people.push_back("Ariel Nowik");
	people.push_back("Marcelo Regueira");

	vector <screenText*> uText(people.size());
	for (int i = 0;i < people.size();i++) {
		uText[i] = new screenText(mySysgame,people[i]);
		uText[i]->configure(people[i],"roboto_v1",
			al_map_rgb(0,0,0),
			pair<float,float>(width/2,height/4 + i * 50),1);
	}

	TextButton *button = new TextButton(mySysgame,"return_button");
	button->generate("VOLVER",g_blue(),pair<float,float>(width / 2,height * 3 / 4),1);

	button->onClick([](Sysgame *sys){
		sys->setNewController(new MenuTest(sys));
	});

	addWidget((Widget*)background);
	addWidget((Widget*)title);
	addWidget((Widget*)info);
	addWidget((Widget*)button);
	for (int i = 0;i < people.size();i++) {
		addWidget((Widget*)uText[i]);
	}
}
void AboutWindow::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void AboutWindow::onNetEvent(NETWORK_EVENT *ev) {

}
AboutWindow::~AboutWindow() {}
