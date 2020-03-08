#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"
#include "../MyGame/MyReadGameData.h"

class MyRoom
{
public:
	explicit MyRoom(MyKey* key, MyMouse* mouse, MyVaribles* vars, MyData* data) {
		this->key = key;
		this->mouse = mouse;
		this->vars = vars;
		this->data = data;
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
	MyData* data;

	bool isOnLogic = false;
	bool isOnRender = false;
};

static void setCurrentRoom(MyRoom** currentRoom, MyRoom* room) {
	if (*currentRoom) {
		(*currentRoom)->onDestroy();
		Safe_Delete(*currentRoom);
	}
	*currentRoom = room;
	room->setCurrentRoom(currentRoom);
}