#include "AboutWindow2.h"

#include <game\controller\aboutWindow\aboutWindow.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\view\widgets\background.h>
#include <framework\view\utils\good_buttons.h>

AboutWindow2::AboutWindow2(Sysgame * sys) : Controller(sys){
}

void AboutWindow2::onCreate()
{
	pair<float, float> size = view->getScreenSize();
	float width = size.first, height = size.second;

	Background *background = new Background(mySysgame, "background");
	background->configureImg(
		"background1",
		pair<float, float>(width / 2, height / 2),
		1);

	screenText *info = new screenText(mySysgame, "info");
	info->configure("Acerca de Stratego", "roboto_v1", al_map_rgb(0, 0, 0), pair<float, float>(10, 15), 0);

	vector <string> credit2;
	credit2.push_back("FUENTES PARA TEXTOS");
	credit2.push_back("CreativeBooster - Fredoka - Free Rounded and Bold Font");
	credit2.push_back("Fontfabric - Akrobat");
	credit2.push_back("Google Fonts - Roboto");
	credit2.push_back("");
	credit2.push_back("INFORMACION ADICIONAL");
	credit2.push_back("YouTube - What Is MVC? Simple Explanation");
	credit2.push_back("stackoverflow - How do I delete a Git branch both locally and remotely?");

	vector <screenText*> credit2Txt(credit2.size());
	for (int i = 0; i < credit2.size(); i++) {
		credit2Txt[i] = new screenText(mySysgame, credit2[i]);
		credit2Txt[i]->configure(credit2[i], "roboto_v1", al_map_rgb(0, 0, 0),
			pair<float, float>(20, 50 + i * 30), 0);
	}

	TextButton *button = new TextButton(mySysgame, "prev_page");
	button->generate("< ANTERIOR", g_blue(), pair<float, float>(width / 4, height * 7 / 8), 1);

	button->onClick([](Sysgame *sys) {
		sys->setNewController((Controller*)new AboutWindow(sys));
	});

	addWidget((Widget*)background);
	addWidget((Widget*)info);
	addWidget((Widget*)button);
	for (int i = 0; i < credit2.size(); i++) {
		addWidget((Widget*)credit2Txt[i]);
	}
}

void AboutWindow2::onNetPack(string & package, map<string, string>& data)
{
}

void AboutWindow2::onNetEvent(NETWORK_EVENT * ev)
{
}

AboutWindow2::~AboutWindow2()
{
}
