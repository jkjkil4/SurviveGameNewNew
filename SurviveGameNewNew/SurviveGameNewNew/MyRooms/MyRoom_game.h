#ifndef _MYROOM_GAME_H
#define _MYROOM_GAME_H

#include "MyRoom.h"
#include "../MyGame/MyPlayer.h"

#include "../MyWidgets/MySolidColorWidget.h"

/*
	��Ҫ�ͷŵĶ���
	��
*/
class MyRoom_game : public MyRoom
{
public:
	explicit MyRoom_game(MyEngine* e);
	~MyRoom_game() override = default;

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;

	void _onResize() override;

	void _onDestroy() override;

	MySave* save = nullptr;

	short* blocks;	//����

	int roomWidth = 400;	//����ķ�������
	int roomHeight = 400;	//����ķ�������
	int blockCount = 160000;	//��������

	MyPlayer player;


	//
	MySolidColorWidget* solidColorWidget = nullptr;
};



#endif //_MYROOM_GMAE_H