#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

void RoomTitle::onLogic() {

}

void RoomTitle::onRender() {
	engine.drawBorder(100, 100, 240, 140, 4, 0xffff88ff);
}