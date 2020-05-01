#pragma once
#include "MyRoom.h"

#include "../MyWidgets/MyPushButton.h"
#include "../MyWidgets/MyTextEdit.h"
#include "../MyWidgets/MyTextWidget.h"
#include "../MyWidgets/MyScrollView.h"
#include "../MyWidgets/MySaveWidget.h"

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

	/*
	visibleFlags
		0 -> �������
		1 -> �浵ѡ�����
			4 -> �½��浵����
			5 -> �浵����������
		2 -> ������Ϸ����
		3 -> ���ý���
	*/

	//��Ҫ���������Ŀؼ�
	MyTextEdit* editSaveName = nullptr;

	//�浵ѡ����б�
	MyScrollView* scrView = nullptr;
	static constexpr int saveWidgetHeight = 42;

	//�浵��Ϣ����ʾ
	MyTextWidget* saveInfoWidget = nullptr;
	MySave* tmpSave = nullptr;
	MySave* shownSave = nullptr;
};

