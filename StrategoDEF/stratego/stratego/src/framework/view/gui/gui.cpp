#include "gui.h"

UIException::UIException(string _err) : err(_err) {

}
const char * UIException::what() const throw() {
	return ("UIException:" + err).c_str();
}


UI::UI() {}

void UI::AddWidget(Widget *widget) {
	if (widgets.find(widget->getName()) != widgets.end()) throw UIException("trying to add to widgets with the same name");
	widgets[widget->getName()] = widget;
}
void UI::RemoveWidget(string name) {
	delete widgets[name];
	widgets.erase(name);
}
void UI::HandleEvent(ALLEGRO_EVENT *ev) {
	for (auto it = widgets.begin(); it != widgets.end(); it++) it->second->handleEvent(ev);
}
void UI::eraseAll() {
	for (auto it = widgets.begin(); it != widgets.end(); it++) delete it->second;
	widgets.clear();
}
UI::~UI() {
	for (auto it = widgets.begin(); it != widgets.end(); it++) delete it->second;
}
