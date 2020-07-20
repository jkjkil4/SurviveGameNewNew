#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

Room_Title::Room_Title() {
	auto m = new ImageLabel(gameData.testImage1);
	addWidget(m);
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {

	Room::onRender();
}