#pragma once

#include <framework\controller\controller.h>

class menuTextView : Controller{
	public:
		menuTextView(Sysgame *sys);
		void drawContent();

		~menuTextView();
};

