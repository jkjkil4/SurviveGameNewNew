#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

Room_Title::Room_Title() {
	auto m = new TextLabel(_T("╡Бйтндвж"), engine.g_pFontSmall, DT_LEFT | DT_TOP, 200, 30);
	addWidget(m);
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {

	Room::onRender();
}