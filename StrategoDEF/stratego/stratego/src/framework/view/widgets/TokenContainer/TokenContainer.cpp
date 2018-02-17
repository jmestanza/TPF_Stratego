#include "TokenContainer.h"

#include <framework\utils\random_number.h>
#include <framework\view\utils\copyBitmap.h>
#include <framework\view\widgets\TokenContainer\MouseFollower.h>
#include <framework\utils\random_number.h>


TokenContainer::TokenContainer(Sysgame *sys,string name) : Widget(sys,name) {
	myCode = "token_container_" + to_string(randomNumber());

	ALLEGRO_BITMAP *bm = view->getImg("token_field");
	this->size = pair<float,float>(al_get_bitmap_width(bm),al_get_bitmap_height(bm));

	buttonLeft = new ButtonRef(sys,myCode + "btnA",this);
	buttonRight = new ButtonRef(sys,myCode + "btnB",this);

	tokenGenerated = 0;
	rel_X = 0;

	//addContent("FB",1);
	//addContent("BB",1);
	//addContent
	borderSize = 69;

	maxPosition = 30 * 10 * content.size() + 10 - this->size.first - 138;

	cnt = 0;
	onTokenSelectFunction = nullptr;
}
void TokenContainer::addAllBlueContent() {
	addContent("FB",1);
	addContent("BB",6);
	addContent("SB",1);
	addContent("1B",8);
	addContent("2B",5);
	addContent("3B",4);
	addContent("4B",4);
	addContent("5B",4);
	addContent("6B",3);
	addContent("7B",2);
	addContent("8B",1);
	addContent("9B",1);
}
void TokenContainer::addAllRedContent() {
	addContent("FR",1);
	addContent("BR",6);
	addContent("SR",1);
	addContent("1R",8);
	addContent("2R",5);
	addContent("3R",4);
	addContent("4R",4);
	addContent("5R",4);
	addContent("6R",3);
	addContent("7R",2);
	addContent("8R",1);
	addContent("9R",1);
}
void TokenContainer::clear() {
	for (auto it = content.begin();it != content.end();it++) {
		it->second.cnt = 0;
	}
	generateTokenContentImage();
}
void TokenContainer::configure(pair<int,int> _pos) {
	pos = _pos;
	//cout << this->pos.first << " " << this->pos.second << '\n';

	pair<float,float> leftPos(this->pos.first + 35,this->pos.second + this->size.second / 2);
	pair<float,float> rightPos(this->pos.first + this->size.first - 35,this->pos.second + this->size.second / 2);

	buttonLeft->generate("",g_greenSmall(),leftPos,1);
	buttonLeft->addIcon("icon_left_dir");

	buttonRight->generate("",g_greenSmall(),rightPos,1);
	buttonRight->addIcon("icon_right_dir");
	int h;
	buttonLeft->onClickToken([](TokenContainer *token){
		token->decRelX();
	});
	buttonLeft->onReleaseToken([](TokenContainer *token) {
		token->stopDecRelX();
	});

	buttonRight->onClickToken([](TokenContainer *token) {
		//rel_X ++;
		token->incRelX();
	});
	buttonRight->onReleaseToken([](TokenContainer *token) {
		//rel_X ++;
		token->stopDecRelX();
	});


	/*onTokenSelect([](Sysgame *sys,string selected) {
		
	});*/
}
void TokenContainer::incRelX() {
	//cout << "inc\n";
	/*rel_X = min(rel_X+35,maxPosition);
	this->generateTokenContentImage();*/
	deltaX = 3;
}
void TokenContainer::decRelX() {
	//cout << "dec\n";
	/*rel_X = max(0,rel_X-35);
	this->generateTokenContentImage();*/
	deltaX = -3;
}
void TokenContainer::stopIncRelX() {
	deltaX = 0;
}
void TokenContainer::stopDecRelX() {
	deltaX = 0;
}
void TokenContainer::handleEvent(ALLEGRO_EVENT *ev) {
	buttonLeft->handleEvent(ev);
	buttonRight->handleEvent(ev);
	if (ev->type == ALLEGRO_EVENT_TIMER) {

		if (deltaX != 0) {
			rel_X += deltaX;
			rel_X = min(rel_X,maxPosition);
			rel_X = max(0,rel_X);


			generateTokenContentImage();
		}
	}else if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mx = ev->mouse.x;
		my = ev->mouse.y;
	}else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		//cout << "button down!\n";
		/// serach if we touched an item
		
		int rx = mx - this->pos.first - borderSize - 10;
		int ry = my - this->pos.second;

		/*if (rx >= 0 && rx <= this->size.first - borderSize) {
			if (ry >= 0 && ry <= this->size.second) {
				rx += rel_X;
				rx /= tokenWidth;
				/// now selected is on x
				if (rx >= 0 && rx < contentOrder.size()) {
					selectItem(rx);
				}
			}
		}*/
		if (ry >= 0 && ry <= this->size.second) {
			for (int i = 0;i < contentOrder.size();i++) {
				if (content[contentOrder[i]].cnt == 0) continue;
				
				if (rx >= content[contentOrder[i]].start_x && rx <= content[contentOrder[i]].end_x) {
					selectItem(contentOrder[i]);
				}
			}
		}
		
	}else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		//cout << "Button up!\n";
	}
}
void TokenContainer::selectItem(string val) {
	//cout << "Selected = " << i << '\n';
	if (onTokenSelectFunction != nullptr) {
		onTokenSelectFunction(mySysgame,val);
	}
	
}
void TokenContainer::startDrawing() {
	view->show("token_field",myCode,pos.first,pos.second);
	buttonLeft->callStartDrawing();
	buttonRight->callStartDrawing();
	if (!tokenGenerated) generateTokenContentImage();
	//cout << "Showing " << myCode << '\n';
	view->show(myCode,myCode+"_b",pos.first+69,pos.second);
}
void TokenContainer::stopDrawing() {
	view->stopShow(myCode);
	buttonLeft->stopDrawing();
	buttonRight->stopDrawing();
}
void TokenContainer::generateTokenContentImage() {
	int width_req = 30 * 10 * content.size() + 10;
	ALLEGRO_BITMAP *bitmapContent = al_create_bitmap(width_req,89);

	int posx = 10;
	for (int i = 0;i < contentOrder.size();i++){
		if ( content[contentOrder[i]].cnt == 0) continue;
		auto it = content.find(contentOrder[i]);
		string tokenCode = "token_" + it->first + "_r";
		
		ALLEGRO_BITMAP *tokenImg = view->getImg(tokenCode);
		//al_set_target_bitmap(bitmapContent);
		//blitBitmap);
		blitBitmap(bitmapContent,tokenImg,posx ,  5);

		blitText(view,bitmapContent,to_string(it->second.cnt),"roboto_v1","black",posx + 25,65);

		it->second.start_x = posx;
		posx += al_get_bitmap_width(tokenImg);
		posx += 10;
		it->second.end_x = posx;
		tokenWidth = al_get_bitmap_width(tokenImg)+10;

	} 
	ALLEGRO_BITMAP *cutBitmap = al_create_bitmap(this->size.first-138,this->size.second);
	blitBitmap(cutBitmap,bitmapContent,0-rel_X,0);

	//al_set_target_bitmap(al_get_backbuffer(view->getScreen()));
	if (!view->hasLoadedImg(myCode)) {
		view->loadFromBitmap(cutBitmap,myCode);
	} else {
		//cout << "updating! \n";
		view->eraseLoaded(myCode);
		view->loadFromBitmap(cutBitmap,myCode);
		if (this->_beingDrawn) {
			view->changeShowImg(myCode+"_b",myCode);
		}
	}
	tokenGenerated = 1;
	maxPosition = 30 * 10 * content.size() + 10 - this->size.first - 138;
	al_destroy_bitmap(bitmapContent);

}
string TokenContainer::getRandomTokenAndPop() {
	/// O(n) 
	vector <string> cand;
	for (auto it = content.begin();it != content.end();it++) {
		int qty = it->second.cnt;
		while (qty--) cand.push_back(it->first);
	}
	if (cand.size() == 0) {
		return "empty";
	}
	string val = cand[randrange(0,cand.size())];
	content[val].cnt --;
	return val;
}

void TokenContainer::addContent(string tokenCode,int qty) {
	if (content.find(tokenCode) == content.end()) {
		contentOrder.push_back(tokenCode);
	}
	content[tokenCode] = Element(qty,0,0);
}
void TokenContainer::removeContent(string tokenCode) {
	content[tokenCode].cnt--;
	generateTokenContentImage();
}
void TokenContainer::incContent(string tokenCode) {
	if (content.find(tokenCode) == content.end()) {
		contentOrder.push_back(tokenCode);
		content[tokenCode] = Element(0,0,0);
	}
	content[tokenCode].cnt ++;
	generateTokenContentImage();
}

TokenContainer::~TokenContainer() {
	delete buttonLeft;
	delete buttonRight;
}

void TokenContainer::onTokenSelect(void (*func)(Sysgame*,string)) {
	onTokenSelectFunction = func;
}