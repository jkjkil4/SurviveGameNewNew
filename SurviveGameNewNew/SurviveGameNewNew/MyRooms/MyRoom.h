#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"

class MyRoom
{
public:
	explicit MyRoom(MyKey* key, MyMouse* mouse, MyVaribles* vars) {
		this->key = key;
		this->mouse = mouse;
		this->vars = vars;
	}
	void setCurrentRoom(MyRoom** currentRoom) {
		this->currentRoom = currentRoom;
	}
	virtual int onLogic() { return 0; }
	virtual int onRender() { return 0; }
	virtual void onDestroy(){}

	MyRoom** currentRoom = nullptr;

	MyKey* key;
	MyMouse* mouse;
	MyVaribles* vars;
};

static void setCurrentRoom(MyRoom** currentRoom, MyRoom* room) {
	if (*currentRoom) {
		(*currentRoom)->onDestroy();
		Safe_Delete(*currentRoom);
	}
	*currentRoom = room;
	room->setCurrentRoom(currentRoom);
}