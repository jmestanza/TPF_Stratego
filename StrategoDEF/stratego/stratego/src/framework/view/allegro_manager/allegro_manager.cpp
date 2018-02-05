#define _WIN32_WINNT 0x0501


#include "allegro_manager.h"
#include "allegro5\allegro5.h"
#include "allegro5\allegro_acodec.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_image.h"
#include <map>
#include <iostream>
using namespace std;

AllegroHandlerException::AllegroHandlerException(string _err) : err(_err) {

}
const char * AllegroHandlerException::what() const throw() {
	return err.c_str();
}
void allegro_init(void) {
	if (!al_init())	throw AllegroHandlerException("could not start allegro");
	if (!al_install_keyboard()) throw AllegroHandlerException("could not start allegro keyboard");
	if (!al_init_image_addon()) throw AllegroHandlerException("could not start allegro image");
	if (!al_install_audio()) throw AllegroHandlerException("could not start allegro audio");
	if (!al_init_acodec_addon()) throw AllegroHandlerException("could not start allegro acodec addon");
	if (!al_reserve_samples(1)) throw AllegroHandlerException("could not start allegro reserve samples");
}
Viewer::Viewer() {
	allegro_init();
}
void Viewer::load(string dir, string name) {
	ALLEGRO_BITMAP* image = al_load_bitmap(dir.c_str());

	if (image == NULL) throw AllegroHandlerException("unable to load image '"+dir+"'");
	
	loaded[name] = image;
}
void Viewer::destroy(string destroyName) {
	loaded.erase(destroyName);
}
void Viewer::draw() {
	vector <int> eraseList;
	for (int i = 0; i < drawOrder.size(); i++) {
		// si se da esta condiccion la imagen fue eliminada, lo agregamos a la lista para la eliminacion definitiva
		if (frontShow.find(drawOrder[i]) == frontShow.end()) {
			eraseList.push_back(i);
		}else {
			ShowObject &obj = frontShow[drawOrder[i]];
			al_draw_bitmap(obj.bitmap, obj.pos.first, obj.pos.second, 0);
		}
	}
	for (int i = eraseList.size() - 1; i >= 0; i--) drawOrder.erase(drawOrder.begin() + eraseList[i]);
}
void Viewer::show(string imageName, string showName, float x, float y) {
	if (loaded.find(imageName) == loaded.end()) throw AllegroHandlerException("invalid usage of Viwer::Show()");
	frontShow[showName] = ShowObject(loaded[imageName],x,y);
	drawOrder.push_back(showName);
}
void Viewer::changeShowImg(string showName, string newImageName) {
	if (loaded.find(newImageName) == loaded.end()) throw AllegroHandlerException("invalid usage of Viwer::ChangeShowImg()");
	if (frontShow.find(showName) == frontShow.end()) throw AllegroHandlerException("invalid usage of Viwer::ChangeShowImg()");

	float x = frontShow[showName].pos.first, y = frontShow[showName].pos.second;
	frontShow[showName] = ShowObject(loaded[newImageName], x, y);
}
void Viewer::destroyAll() {
	loaded.clear();
}
Viewer::~Viewer() {
	for (auto it = loaded.begin(); it != loaded.end(); it++) al_destroy_bitmap(it->second);
}
