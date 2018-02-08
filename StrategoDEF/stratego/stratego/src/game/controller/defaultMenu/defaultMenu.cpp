#include "defaultMenu.h"



defaultMenu::defaultMenu(Sysgame* sys) : Controller(sys){}

void defaultMenu::onCreate() {

}
void defaultMenu::onNetPack(string &package,map<string,string> &data) {}// handle NETWORK actions
void defaultMenu::onNetEvent(NETWORK_EVENT *ev) {
}

defaultMenu::~defaultMenu() {}
