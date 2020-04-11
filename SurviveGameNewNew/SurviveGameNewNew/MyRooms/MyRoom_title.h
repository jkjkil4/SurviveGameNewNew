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
		0 -> �������
		1 -> �浵ѡ�����
			4 -> �½��浵����
		2 -> ������Ϸ����
		3 -> ���ý���
	*/
	int visibleFlags = 0;

	//��Ҫ���������Ŀؼ�
	MyTextEdit* editSaveName = nullptr;
};

