#pragma once

#include "MyRoom.h"
#include "../MyGame/MyPlayer.h"
#include "../MyGame/MyReadGameData.h"

class MyRoom_game : public MyRoom
{
public:
	explicit MyRoom_game(MyKey* key, MyMouse* mouse, MyVaribles* vars, MyData* data, int roomWidth, int roomHeight);

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);

	int onLogic() override;
	int onRender() override;
	void onDestroy() override;

	int* blocks;

	int roomWidth = 400;	//����ķ�������
	int roomHeight = 400;	//����ķ�������
	int blockCount = 160000;

	LPD3DXSPRITE g_pSpritePlayer;
	MyPlayer player;

	//��ʱ
};

