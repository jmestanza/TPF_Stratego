#include "aboutWindow.h"

#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\background.h>
#include <game\controller\menu_test\menu_test.h>
#include <game\controller\aboutWindow2\AboutWindow2.h>
#include <framework\view\utils\good_buttons.h>

AboutWindow::AboutWindow(Sysgame* sys) : Controller(sys){
}
void AboutWindow::onCreate() {

	pair<float,float> size = view->getScreenSize();
	float width = size.first,height = size.second;

	screenText *info = new screenText(mySysgame, "info");
	info->configure("Acerca de Stratego", "roboto_v1", al_map_rgb(0, 0, 0), pair<float, float>(10, 15), 0);
	
	screenText *title = new screenText(mySysgame,"title");
	title->configure("22.08 Algoritmos y estructura de datos - TPF","roboto_v30",al_map_rgb(0,0,0),
		pair<float,float>(width / 2,height / 9),
		1);

	Background *background = new Background(mySysgame,"background");
	background->configureImg(
		"background1",
		pair<float, float>(width / 2, height / 2),
		1);

	screenText *develop = new screenText(mySysgame, "develop");
	develop->configure("DESARROLLADORES", "roboto_v1", al_map_rgb(0, 0, 0), pair<float, float>(width / 2, height / 4 - 50), 1);

	vector <string> people;
	people.push_back("Joaquin Mestanza");
	people.push_back("Ariel Nowik");
	people.push_back("Marcelo Regueira");

	vector <screenText*> uText(people.size());
	for (int i = 0;i < people.size();i++) {
		uText[i] = new screenText(mySysgame,people[i]);
		uText[i]->configure(people[i],"roboto_v1",
			al_map_rgb(0,0,0),
			pair<float,float>(width/2,height/4 + i * 30),1);
	}

	vector <string> credit1;
	credit1.push_back("PARSEO DE XML CON BOOST");
	credit1.push_back("Andrzej's C++ blog - Parsing xml with Boost (Julio 13, 2011)");
	credit1.push_back("");
	credit1.push_back("EXCEPCIONES EN C++");
	credit1.push_back("Quora - How does one write a custom exception class in C++?");
	credit1.push_back("");
	credit1.push_back("MUSICA");
	credit1.push_back("YoutTube - Celtic Medieval Music - Kingdom of bards");
	credit1.push_back("ICONOS");
	credit1.push_back("freepik - Free icons, +99,400 files in PNG, EPS, SVG format");
	credit1.push_back("Noun Project - ip");
	credit1.push_back("Flaticon - Free icons designed by:");
	credit1.push_back(" - Gregor Cresnar");
	credit1.push_back(" - Swifticons");
	credit1.push_back(" - Pixelmeetup");
	credit1.push_back(" - DinosoftLabs");
	credit1.push_back(" - Lucy G");

	vector <screenText*> credit1Txt(credit1.size());
	for (int i = 0; i < credit1.size(); i++) {
		credit1Txt[i] = new screenText(mySysgame, credit1[i]);
		if (i < 8) {
			credit1Txt[i]->configure(credit1[i], "roboto_v1", al_map_rgb(0, 0, 0),
				pair<float, float>(20, height / 2 + i * 30 - 50), 0);
		}
		else {
			credit1Txt[i]->configure(credit1[i], "roboto_v1", al_map_rgb(0, 0, 0),
				pair<float, float>(20 + width / 2, height / 2 + (i-8) * 30 - 50), 0);
		}


	}

	TextButton *button = new TextButton(mySysgame,"return_button");
	button->generate("VOLVER",g_blue(),pair<float,float>(width / 4,height * 7 / 8),1);

	button->onClick([](Sysgame *sys){
		sys->setNewController(new MenuTest(sys));
	});

	TextButton *button2 = new TextButton(mySysgame,"next_page");
	button2->generate("SIGUIENTE >", g_blue(), pair<float, float>(width / 4 * 3, height * 7 / 8), 1);

	button2->onClick([](Sysgame *sys) {
		sys->setNewController((Controller*)new AboutWindow2(sys));
	});

	addWidget((Widget*)background);
	addWidget((Widget*)develop);
	addWidget((Widget*)title);
	addWidget((Widget*)info);
	addWidget((Widget*)button);
	addWidget((Widget*)button2);
	for (int i = 0;i < people.size();i++) {
		addWidget((Widget*)uText[i]);
	}
	for (int i = 0; i < credit1.size(); i++) {
		addWidget((Widget*)credit1Txt[i]);
	}
}
void AboutWindow::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void AboutWindow::onNetEvent(NETWORK_EVENT *ev) {

}
AboutWindow::~AboutWindow() {}
