#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"
#include "../MyGame/MyReadGameData.h"
#include "../MyViewControls/MyViewControl.h"

#define MyDebug 1

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
	virtual void onDestroy() {}
	void publicDestroy() {
		//delete窗口控件
		for (int i = 0; i < (int)(vec_viewControl.size()); i++) {
			Safe_Delete(vec_viewControl[i]);
		}
	}
#if MyDebug
	void onDebug(){}
#endif

	MyRoom** currentRoom = nullptr;

	MyKey* key;
	MyMouse* mouse;
	MyVaribles* vars;
	MyData* data;

	int fps = 0;
	int startGetFps = 0;
	int fpsCount = 0;
	
	//存放窗口控件的vector
	std::vector<MyViewControl*> vec_viewControl;
};

static void setCurrentRoom(MyRoom** currentRoom, MyRoom* room) {
	if (*currentRoom) {
		(*currentRoom)->onDestroy();
		Safe_Delete(*currentRoom);
	}
	*currentRoom = room;
	room->setCurrentRoom(currentRoom);
}