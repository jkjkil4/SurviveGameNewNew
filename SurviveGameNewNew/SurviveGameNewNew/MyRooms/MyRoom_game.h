#pragma once

#include "MyRoom.h"
#include "../MyGame/MyPlayer.h"
#include "../MyGame/MyReadGameData.h"
/*
	需要释放的对象:
	g_pSpritePlayer
	g_pFont
*/
class MyRoom_game : public MyRoom
{
public:
	explicit MyRoom_game(MyKey* key, MyMouse* mouse, MyVaribles* vars, MyData* data, int roomWidth, int roomHeight);

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);
	
	int onLogic() override;
	int onRender() override;
	void onDestroy() override;
#if MyDebug
	void onDebug();
#endif

	int* blocks;

	int roomWidth = 400;	//横向的方块数量
	int roomHeight = 400;	//纵向的方块数量
	int blockCount = 160000;

	LPD3DXSPRITE g_pSpritePlayer;
	LPD3DXFONT g_pFont;
	MyPlayer player;

};

