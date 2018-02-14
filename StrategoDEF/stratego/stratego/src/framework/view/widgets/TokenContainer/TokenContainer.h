#pragma once

#include <framework\view\widgets\widget.h>
#include <framework\view\widgets\naive_button.h>
#include <framework\view\utils\good_buttons.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\Table.h>

#include <map>

using namespace std;
class TokenContainer;

class ButtonRef : public TextButton {
	private:
		void(*func)(TokenContainer *);
		void(*funcB)(TokenContainer *);

	public:
		TokenContainer * ref;


		ButtonRef(Sysgame *sys,string code,TokenContainer * _ref) : TextButton(sys,code),ref(_ref) {}
		void onHardClickToOverride() {
			func(ref);
		//	cout << "to override \n";
		}
		void onReleaseToOverride() {
			funcB(ref);
		}
		void onClickToken(void(*_func)(TokenContainer*)) {
			func = _func;
		}
		void onReleaseToken(void(*_func)(TokenContainer*)) {
			funcB = _func;
		}
};

class Table;

struct Element {
	int cnt;
	int start_x;
	int end_x;
	Element(int c,int sx,int ex) {
		cnt = c; start_x = sx; end_x = ex;
	}
	Element() {}
};

class TokenContainer : public Widget{
	private:
		map <string,Element> content;

		vector <string> contentOrder;
		int rel_X; /// focus current position
		string myCode;

		Table *tableRef;
		
		ButtonRef *buttonLeft;
		ButtonRef *buttonRight;

		bool tokenGenerated;
		int borderSize;
		int maxPosition;
		int deltaX;
		int cnt;
		int mx,my;
		int tokenWidth;
		void (*onTokenSelectFunction)(Sysgame *,string);

	public:
		TokenContainer(Sysgame *sys,string name);
		~TokenContainer();
		void configure(pair<int,int> pos);

		void handleEvent(ALLEGRO_EVENT *ev);
		void startDrawing();
		void stopDrawing();

		void addContent(string tokenCode,int qty);
		void removeContent(string tokenCode);
		void generateTokenContentImage();
		void incRelX();
		void decRelX();
		void stopDecRelX();
		void stopIncRelX();
		void selectItem(string val);
		void onTokenSelect(void (*func)(Sysgame*,string) );
		void incContent(string tokenCode);
		void setTableRef(Table *tbl);
};

