#include "gui.h"
#include <iostream>
using namespace std;

UIException::UIException(string _err) : err("UIException:" + _err) {

}
const char * UIException::what() const throw() {
	return ( err).c_str();
}


UI::UI() {}

void UI::AddWidget(Widget *widget) {
	if (widgets.find(widget->getName()) != widgets.end()) {
		throw UIException("trying to add to widgets with the same name, '" + widget->getName() + "' ");
	}
	addWidgets.push_back(widget);
	
	//widgets[widget->getName()] = widget;
	//widget->startDrawing();
}
void UI::RemoveWidget(string name) {
	if (widgets.find(name) != widgets.end()) {
		widgets[name]->killMe();
		
		deadWidgets.push_back(name);
	} else {
		cout << "warning: trying to delete un-existing widgets\n";
	}
}
void UI::refreshDead() {
	for (int i = 0;i < addWidgets.size();i++) {
		widgets[addWidgets[i]->getName()] = addWidgets[i];
		widgets[addWidgets[i]->getName()]->callStartDrawing();
	}
	addWidgets.clear();
	for (int i = 0;i < deadWidgets.size();i++) {
		if (widgets.find(deadWidgets[i]) == widgets.end()) continue; // can happen because syncronization
		widgets[deadWidgets[i]]->callStopDrawing();
		delete widgets[deadWidgets[i]];
		widgets.erase(deadWidgets[i]);
	}
	deadWidgets.clear();
}
void UI::HandleEvent(ALLEGRO_EVENT *ev) {
	for (auto it = widgets.begin(); it != widgets.end(); it++) it->second->handleEvent(ev);
}
void UI::eraseAll() {
	for (auto it = widgets.begin(); it != widgets.end(); it++) RemoveWidget(it->first);
}
Widget* UI::getWidget(string name) {
	if (widgets.find(name) == widgets.end()) {
		return nullptr;
		//throw UIException("Trying to access to widget '"+name+"' that don't exist");
	}
	return widgets[name];
}
UI::~UI() {
	eraseAll();
	refreshDead();
}
