#ifndef _MYROOM_GAME_H
#define _MYROOM_GAME_H

#include "MyRoom.h"
#include "../MyGame/MyPlayer.h"

/*
	需要释放的对象
	g_pFont
*/
class MyRoom_game : public MyRoom
{
public:
	explicit MyRoom_game(MyEngine* e);
	~MyRoom_game() override;

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);

	void onLogic() override;
	void onRender() override;
	void onDebug() override;

	void onDestroy() override;

	int* blocks;	//方块

	int roomWidth = 400;	//横向的方块数量
	int roomHeight = 400;	//纵向的方块数量
	int blockCount = 160000;	//方块数量

	MyPlayer player;

	LPD3DXFONT g_pFont = nullptr;
};



#endif //_MYROOM_GMAE_H