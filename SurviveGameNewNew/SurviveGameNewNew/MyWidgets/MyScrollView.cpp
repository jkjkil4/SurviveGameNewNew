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
		w->move(0, index * (childH + borderWidth) + offset);
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
void MyScrollView::limitOffset(int minOffset) {
	
	if (offset > 0) {
		int limitSpd = 2 + (offset) / 4;
		offset -= limitSpd;
		if (offset < 0)
			offset = 0;
	}
	else if (offset < minOffset) {
		int limitSpd = 2 + (minOffset - offset) / 4;
		offset += limitSpd;
		if (offset > minOffset)
			offset = minOffset;
	}
	updateChildPos();
}

void MyScrollView::clear() {
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* child = *it;
		child->onDestroy();
		safeDelete(child);
	}
	childs.clear();

	spd = 0;
	offset = 0;
}

inline void MyScrollView::_onRender(LPD3DXSPRITE, int, int) {
	if (spd != 0) {
		sumSpdToOffset();
		updateChildPos();
	}

	int min = myMin<int>(h - (childH + borderWidth) * childs.size() + borderWidth, 0);
	if (offset > 0 || offset < min)
		limitOffset(min);
}

inline void MyScrollView::_wheelEvent(int, int, int delta) {
	int num = delta / 20;
	if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
		spd = 0;
	spd += num;
	if (abs(spd) > 8)
		spd > 0 ? spd = 20 : spd = -20;
}