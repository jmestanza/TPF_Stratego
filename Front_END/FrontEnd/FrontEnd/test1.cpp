#include "Viewer.h"
#include "UI.h"
#include "naiveButton.h"
#include <iostream>
#include <exception>
using namespace std;
int main() {
	cout << ALLEGRO_EVENT_MOUSE_BUTTON_DOWN << '\n';

	Viewer viewer;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *q;
	try{
		viewer = Viewer();
		display = al_create_display(800, 600);
		al_install_mouse();
		q = al_create_event_queue();
		al_register_event_source(q, al_get_display_event_source(display));
		al_register_event_source(q, al_get_keyboard_event_source());
		al_register_event_source(q, al_get_mouse_event_source());
		
		viewer.load("1510172827500.jpg", "cat");
		viewer.load("ui/buttons/button_test_v1/g4203.png", "simple_button_img1");
		viewer.load("ui/buttons/button_test_v1/g4825.png", "simple_button_img2");
		viewer.load("ui/buttons/button_test_v1/g4827.png", "simple_button_img3");
	} catch (ViewerException &e) {
		cerr << "error: " << e.what() << '\n';
		cin.ignore();
		return 0;
	}

	UI ui = UI();
	ui.AddWidget( (Widget*)new NaiveButton(&viewer,pair<float,float>(20,20),0,"simple_button_img1","simple_button_img2"),"button1");

	bool exit = 0;
	while (!exit) {
		if (al_get_next_event(q, &ev)) {
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit = 1;
			ui.HandleEvent(&ev);
		}
		viewer.draw();
		al_flip_display();
	}
	al_destroy_event_queue(q);
	al_destroy_display(display);
}