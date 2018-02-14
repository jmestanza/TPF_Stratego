#include "showTimeTest.h"

#include <framework\view\widgets\background.h>
#include <framework\view\widgets\showClocks\showTime.h>
#include <framework\view\widgets\Table.h>
#include <framework\view\widgets\widget.h>
#include <framework\view\widgets\TokenContainer\TokenContainer.h>
#include <framework\view\widgets\TokenContainer\MouseFollower.h>

showTimeTest::showTimeTest(Sysgame *sys) : Controller(sys) {}

void showTimeTest::onCreate() {
	addBackgroundImg("background1");
	selectedItem = "";

	pair <float,float> screenSize = view->getScreenSize();

	Table* tablero = new Table(mySysgame,"table","test_blue","test_red",pair<float,float>(60,60),1);
	tablero->setPos(pair<float,float>(20 + tablero->getSize().first / 2,screenSize.second / 2),1);
	tablero->setPlayersName("ARIEL","JOAQUIN");


	addWidget((Widget*)tablero);
	
	TokenContainer *cont = new TokenContainer(mySysgame,"token_container");
	int halfPoint = (tablero->getPos().first + tablero->getSize().first + screenSize.first)/2;
	pair <float,float> posToken(halfPoint-cont->getSize().first/2,screenSize.second - cont->getSize().second - 70);

	cont->configure( posToken );

	cont->onTokenSelect([](Sysgame *sys,string selected) {
		showTimeTest* myself = (showTimeTest*)sys->getController();
		myself->setSelectedItem(selected);
		
		Table *board = (Table*)sys->getUI()->getWidget("table");
		board->informSelected(selected);
	});

	tablero->onMouseRelease([](Sysgame *sys,Table *table,pair<int,int> pos) {
		MouseFollower *follow = (MouseFollower*)sys->getUI()->getWidget("mouse_selected");
		//follow->
		showTimeTest *controller = (showTimeTest*)sys->getController();
		if (controller->getSelectedItem() != "") {
			table->putToken(controller->getSelectedItem(),pos);
		}
	});

	addWidget((Widget*)cont);

	MouseFollower *follow = new MouseFollower(mySysgame,"mouse_selected");
	//follow->setImg("token_" + selected + "_r");

	addWidget((Widget*)follow);
	/*Background* back = new Background(mySysgame,"background");
	back->configure("light_blue",pair<float,float>(0,0),view->getScreenSize(),0);

	float screenWidth = view->getScreenSize().first, screenHeight = view->getScreenSize().second;
	pair<float,float> screenHalf = pair<float,float>(screenWidth/2,screenHeight/2);
	ShowTime *showTime = new ShowTime(mySysgame,"show_time");
	showTime->configure("roboto_v30","black",screenHalf,1);
	showTime->setTarget(70000);
	showTime->showMillis();
	showTime->showMinutes();

	addWidget((Widget*)back);
	addWidget((Widget*)showTime);*/


	//Table(Sysgame*Sys,string _name,string _img_a,string _img_b,pair<float,float> _screen_center,pair<float,float>_pieceSize);


}

string showTimeTest::getSelectedItem() {
	return selectedItem;
}
void showTimeTest::setSelectedItem(string value) {
	selectedItem = value;
	((MouseFollower*)mySysgame->getUI()->getWidget("mouse_selected"))->setImg("token_"+value+"_r");
	
}

void showTimeTest::onNetPack(string &package,map<string,string> &data) {

}// handle NETWORK actions
void showTimeTest::onNetEvent(NETWORK_EVENT *ev) {

}

showTimeTest::~showTimeTest() {}
