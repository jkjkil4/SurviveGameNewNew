#include "Engine.h"

#include "../Room/Room.h"

using namespace My;

void Engine::setCurrentRoom(Room* room) {
	if (currentRoom) {
		currentRoom->onDestroy();
		safeDelete(currentRoom);
	}
	currentRoom = room;
}