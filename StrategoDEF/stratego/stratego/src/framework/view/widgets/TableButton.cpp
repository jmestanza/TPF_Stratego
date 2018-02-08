#include "TableButton.h"

TableButton::TableButton(string _def_img, pair<float, float> _pos, pair<float, float> _size, Sysgame * sys, string _name) :Widget(sys, _name)
{
	default_img = _def_img;
	// size fijo
	size = _size;
	pos = _pos;
	name = _name;
}

void TableButton::handleEvent(ALLEGRO_EVENT *ev) {

}
void TableButton::startDrawing() {

}
TableButton::~TableButton()
{
}
