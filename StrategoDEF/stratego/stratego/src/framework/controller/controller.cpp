#include "controller.h"

#include <framework\view\widgets\showClocks\showTime.h>
#include <framework\utils\random_number.h>
#include <framework\view\widgets\background.h>

Controller::Controller(Sysgame *_sysgame) : mySysgame(_sysgame) {
	view = _sysgame->getAllegroHandler();
}
void Controller::addWidget(Widget *widget) {
	mySysgame->getUI()->AddWidget(widget);
}
void Controller::eraseWidget(string name) {
	mySysgame->getUI()->RemoveWidget(name);
}
void Controller::callIn(int miliseconds,void(*func)(Sysgame *)) {

	if (flagTimer) {
		cout << "warning, controller only supports one timer at the same time \n";
		return;
	}
	pair <float,float> screenSize = view->getScreenSize();
	pair <float,float> outScreen = pair<float,float>(screenSize.first + 10,screenSize.second + 10);
	timerName = "clock_wait_time_"+to_string(randomNumber());
	ShowTime *showTime = new ShowTime(mySysgame,timerName);

	timerFunc = func;
	showTime->setTarget(1000);
	showTime->configure("roboto_v30","black",outScreen,0);
	showTime->onTime([](Sysgame *sys) {
		sys->getController()->callTimerFunc();
		sys->getController()->disableFlagTimer();
		sys->getUI()->RemoveWidget(sys->getController()->getTimerName());
	});
	addWidget((Widget*)showTime);
}
void Controller::callTimerFunc() {
	timerFunc(mySysgame);
}
void Controller::disableFlagTimer() {
	flagTimer = 0;
}
void Controller::addBackgroundImg(string img) {
	pair<float,float> screenSize = view->getScreenSize();
	Background *background = new Background(mySysgame,"background");
	background->configureImg(
		"background1",
		pair<float,float>(screenSize.first / 2,screenSize.second / 2),
		1);
	addWidget((Widget*)background);
}
string Controller::getTimerName() {
	return timerName;
}
Controller::~Controller() {

}