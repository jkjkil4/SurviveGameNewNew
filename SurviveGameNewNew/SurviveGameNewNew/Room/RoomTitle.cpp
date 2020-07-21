#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

Room_Title::Room_Title() {
	int sum = 10;
	repeat(i, 10) {
		Widget* w = new ImageLabel(gameData.testImage1, Align::Left | Align::Top);
		w->move(sum + i * 25, 10 + i * 25);
		sum += rand() % 35;
		addWidget(w);
	}
	repeat(i, 10) {
		Button* btn = new Button(gameData.testImage2, _T("²âÊÔ"), engine.g_pFontSmall, DT_CENTER | DT_VCENTER, Align::Left | Align::Top);
		btn->move(rand() % 400, rand() % 400);
		btn->setSlot(this, (PushButtonFunc)&Room_Title::test);
		addWidget(btn);
	}
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {

	Room::onRender();
}