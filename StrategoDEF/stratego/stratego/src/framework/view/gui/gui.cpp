#include "gui.h"

UIException::UIException(string _err) : err(_err) {

}
const char * UIException::what() const throw() {
	return ("UIException:" + err).c_str();
}


UI::UI() {}

void UI::AddWidget(Widget *widget) {
	if (widgets.find(widget->getName()) != widgets.end()) throw UIException("trying to add to widgets with the same name");
	addWidgets.push_back(widget);
	
	//widgets[widget->getName()] = widget;
	//widget->startDrawing();
}
void UI::RemoveWidget(string name) {
	if (widgets.find(name) != widgets.end()) {
		widgets[name]->killMe();
		
		deadWidgets.push_back(name);
	}
}
void UI::refreshDead() {
	for (int i = 0;i < addWidgets.size();i++) {
		widgets[addWidgets[i]->getName()] = addWidgets[i];
		widgets[addWidgets[i]->getName()]->startDrawing();
	}
	addWidgets.clear();
	for (int i = 0;i < deadWidgets.size();i++) {
		widgets[deadWidgets[i]]->stopDrawing();
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
UI::~UI() {
	eraseAll();
	refreshDead();
}
