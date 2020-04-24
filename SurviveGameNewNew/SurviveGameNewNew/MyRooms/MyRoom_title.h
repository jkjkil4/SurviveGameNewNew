#pragma once
#include "MyRoom.h"

#include "../MyWidgets/MyPushButton.h"
#include "../MyWidgets/MyTextEdit.h"
#include "../MyWidgets/MyTextWidget.h"
#include "../MyWidgets/MyScrollView.h"

class MyRoom_title : public MyRoom
{
private:


public:
	MyRoom_title(MyEngine* e);
	~MyRoom_title() override = default;

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;
	void _onDestroy() override;

	void loadSavesList();
	std::vector<MySave*> saves;

	void btnSiglePressed(MyMouseEvent ev);
	void btnMultiPressed(MyMouseEvent ev);
	void btnSettingsPressed(MyMouseEvent ev);
	void btnExitPressed(MyMouseEvent ev);

	void btnSigleJoinPressed(MyMouseEvent ev);
	void btnSigleRenamePressed(MyMouseEvent ev);
	void btnSigleDeletePressed(MyMouseEvent ev);
	void btnSigleCreatePressed(MyMouseEvent ev);
	void btnSigleBackPressed(MyMouseEvent ev);

	void btnCreateBackPressed(MyMouseEvent ev);
	void btnCreateAcceptPressed(MyMouseEvent ev);

	MyEngine* e = nullptr;
	int gg = 0;
	/*
	visibleFlags
		0 -> 标题界面
		1 -> 存档选择界面
			4 -> 新建存档界面
		2 -> 多人游戏界面
		3 -> 设置界面
	*/

	//需要保留变量的控件
	MyTextEdit* editSaveName = nullptr;
};

