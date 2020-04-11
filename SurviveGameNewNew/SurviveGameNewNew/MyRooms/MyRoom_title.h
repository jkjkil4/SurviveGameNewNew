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

	void _btnSiglePressed(MyMouseEvent ev);
	void _btnMultiPressed(MyMouseEvent ev);
	void _btnSettingsPressed(MyMouseEvent ev);
	void _btnExitPressed(MyMouseEvent ev);

	void _btnSigleJoinPressed(MyMouseEvent ev);
	void _btnSigleRenamePressed(MyMouseEvent ev);
	void _btnSigleDeletePressed(MyMouseEvent ev);
	void _btnSigleCreatePressed(MyMouseEvent ev);
	void _btnSigleBackPressed(MyMouseEvent ev);

	void _btnCreateBackPressed(MyMouseEvent ev);
	void _btnCreateAcceptPressed(MyMouseEvent ev);

	MyEngine* e = nullptr;

	/*
		0 -> 标题界面
		1 -> 存档选择界面
			4 -> 新建存档界面
		2 -> 多人游戏界面
		3 -> 设置界面
	*/
	int visibleFlags = 0;

	//需要保留变量的控件
	MyTextEdit* editSaveName = nullptr;
};

