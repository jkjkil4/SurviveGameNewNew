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
		0 -> �������

		1 -> �浵ѡ�����

		2 -> ������Ϸ����

		3 -> ���ý���
	*/
	int visibleFlags = 0;
};

