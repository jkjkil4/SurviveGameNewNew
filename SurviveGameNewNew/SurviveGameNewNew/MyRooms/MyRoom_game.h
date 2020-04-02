#ifndef _MYROOM_GAME_H
#define _MYROOM_GAME_H

#include "MyRoom.h"
#include "../MyGame/MyPlayer.h"

/*
	��Ҫ�ͷŵĶ���
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

	int* blocks;	//����

	int roomWidth = 400;	//����ķ�������
	int roomHeight = 400;	//����ķ�������
	int blockCount = 160000;	//��������

	MyPlayer player;

	LPD3DXFONT g_pFont = nullptr;
};



#endif //_MYROOM_GMAE_H