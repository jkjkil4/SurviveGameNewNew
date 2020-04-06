#pragma once
#include "MyRoom.h"

class MyRoom_title : public MyRoom
{
public:
	MyRoom_title(MyEngine* e);
	~MyRoom_title() override;

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;
	void _onDestroy() override;

	void _btnSiglePressed(int mouse);
	void _btnMultiPressed(int mouse);
	void _btnSettingsPressed(int mouse);
	void _btnExitPressed(int mouse);

	void _btnSigleJoinPressed(int mouse);
	void _btnSigleRenamePressed(int mouse);
	void _btnSigleDeletePressed(int mouse);
	void _btnSigleCreatePressed(int mouse);
	void _btnSigleBackPressed(int mouse);

	MyEngine* e = nullptr;

	/*
		0 -> 标题界面

		1 -> 存档选择界面

		2 -> 多人游戏界面

		3 -> 设置界面
	*/
	int visibleFlags = 0;
};

