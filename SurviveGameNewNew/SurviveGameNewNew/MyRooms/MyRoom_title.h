#pragma once
#include "MyRoom.h"

class MyRoom_title : public MyRoom
{
public:
	MyRoom_title(MyKey* key, MyMouse* mouse, MyVaribles* vars)
	: MyRoom(key, mouse, vars)
	{
		onInit();
	}

	void onInit();
	int onLogic() override;
	int onRender() override;
	void onDestroy() override;

	INT t = 0;

	LPD3DXFONT g_pFont = nullptr;	//×ÖÌå¶ÔÏó
};

