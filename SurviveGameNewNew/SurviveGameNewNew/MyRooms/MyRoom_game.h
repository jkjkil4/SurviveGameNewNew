#pragma once

#include "MyRoom.h"

class MyRoom_game : public MyRoom
{
public:
	explicit MyRoom_game(MyKey* key, MyMouse* mouse, MyVaribles* vars)
		: MyRoom(key, mouse, vars)
	{
		onInit();
	}
	void onInit();
	int onLogic() override;
	int onRender() override;
	void onDestroy() override;


};

