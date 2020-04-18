#include "MyScrollView.h"

MyScrollView::MyScrollView(MyEngine* e, int w, int h, MyWidget* parent) 
	: MyWidget(e, w, h, nullptr, parent) 
{
	isAcceptWheelEvent = true;
	useRenderTarget();
}

void MyScrollView::updateChildPos() {
	int index = 0;
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		w->move(0, 2 + index * (childH + 2) + offset);
		index++;
	}
}

void MyScrollView::sumSpdToOffset() {
	offset += spd;
	if (spd > 0) {
		spd -= 1;
		if (spd < 0)
			spd = 0;
	}
	else if (spd < 0) {
		spd += 1;
		if (spd > 0)
			spd = 0;
	}
}

inline void MyScrollView::_onRender(LPD3DXSPRITE, int, int) {
	if (spd != 0) {
		sumSpdToOffset();
		updateChildPos();
	}
}

inline void MyScrollView::_wheelEvent(int, int, int delta) {
	int num = -delta / 20;
	if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
		spd = 0;
	spd += num;
	if (abs(spd) > 8)
		spd > 0 ? spd = 20 : spd = -20;
}