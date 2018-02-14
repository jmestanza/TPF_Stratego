#pragma once

#include <framework\view\widgets\widget.h>

class MouseFollower : public Widget{
	private:
		string myBitmap;
		int mx,my;

		int updated;
		int inScreen;
	public:
		MouseFollower(Sysgame *sys,string name);
		void setMouse(int _mx,int _my);
		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();
		void setImg(string _img);
		void hide();

		~MouseFollower();
};

