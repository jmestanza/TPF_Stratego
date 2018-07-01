#include "ShowObject.h"

ShowObject::ShowObject(Viewer *_view) : view(_view){
	sizeSet = 0;
}
void ShowObject::setPosition(pair<float, float> position,bool centered) {
	if (sizeSet && centered) {
		position.first  -= size.first / 2;
		position.second -= size.second / 2;
	}
	pos = position;
}
void ShowObject::setSize(pair<float, float> _size) {
	sizeSet = 1;
	size = _size;
}

ShowObject::~ShowObject() {}
