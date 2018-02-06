#include "gui.h"



UI::UI() {}

bool UI::AddWidget(Widget *widget, string name) {
	if (widgets.find(name) != widgets.end()) return 0;
	widgets[name] = widget;
	return 1;
}
void UI::RemoveWidget(string name) {
	widgets.erase(name);
}
void UI::HandleEvent(ALLEGRO_EVENT *ev) {
	for (auto it = widgets.begin(); it != widgets.end(); it++) it->second->handleEvent(ev);
}
void UI::eraseAll() {
	widgets.clear();
}
UI::~UI() {
	for (auto it = widgets.begin(); it != widgets.end(); it++) delete it->second;
}
