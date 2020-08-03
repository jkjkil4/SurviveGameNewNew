#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;
using namespace std;

Room_Title::Room_Title() {
	visibleNum = VF_Title;

	{//标题界面
		SC int offY = 40;

		Button* btnSigleplayer = new Button(gameData.btnBig, _T("单人游戏"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSigleplayer->move(0, -70 + offY);
		btnSigleplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSigleplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnSigleplayerClicked);
		addWidget(btnSigleplayer);

		Button* btnMultiplayer = new Button(gameData.btnBig, _T("多人游戏(没做)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnMultiplayer->move(0, offY);
		btnMultiplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnMultiplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnMultiplayerClicked);
		addWidget(btnMultiplayer);

		Button* btnSettings = new Button(gameData.btnBig, _T("设置(没做)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSettings->move(0, 70 + offY);
		btnSettings->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSettings->setSlot(this, (ButtonFunc)&Room_Title::onBtnSettingsClicked);
		addWidget(btnSettings);

		Button* btnExit = new Button(gameData.btnBig, _T("退出"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnExit->move(0, 140 + offY);
		btnExit->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnExit->setSlot(this, (ButtonFunc)&Room_Title::onBtnExitClicked);
		addWidget(btnExit);
	}
	{//存档选择界面
		ImageLabel* widget = new ImageLabel(gameData.saveSelect);
		widget->setVisibleOperation(new OperationClass_Equal(VF_SaveSelect), &visibleNum);
		addWidget(widget);

		TextLabel* textLabel = new TextLabel(_T("选择存档"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
		textLabel->textColor = 0xffcccccc;

		Button* btnBack = new Button(gameData.btnSmall, _T("返回"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackClicked);

		Button* btnCreate = new Button(gameData.btnSmall, _T("新建"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnCreate->move(175, 5);
		btnCreate->setSlot(this, (ButtonFunc)&Room_Title::onBtnCreateClicked);

		Button* btnJoin = new Button(gameData.btnMedium, _T("进入"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnJoin->move(5, 5);
		btnJoin->setSlot(this, (ButtonFunc)&Room_Title::onBtnSigleplayerJoinClicked);

		Button* btnRename = new Button(gameData.btnVerySmall, _T("重命名"), engine.g_pFontVerySmall, 
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnRename->move(88, 46);
		btnRename->setSlot(this, (ButtonFunc)&Room_Title::onBtnSaveRenameClicked);

		Button* btnDelete = new Button(gameData.btnVerySmall, _T("删除"), engine.g_pFontVerySmall, 
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnDelete->move(5, 46);
		btnDelete->setSlot(this, (ButtonFunc)&Room_Title::onBtnSaveDeleteClicked);
	}
	{//存档创建界面 /同时也是存档重命名界面
		ImageLabel* widget = new ImageLabel(gameData.saveCreate);
		widget->setVisibleOperation(new OperationClass_AnyEqual({VF_SaveCreate, VF_SaveRename}), &visibleNum);
		addWidget(widget);

		Button* btnBack = new Button(gameData.btnSmall, _T("返回"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackToSelectClicked);

		{//存档创建界面
			TextLabel* textLabel = new TextLabel(_T("创建存档"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
			textLabel->setVisibleOperation(new OperationClass_Equal(VF_SaveCreate), &visibleNum);
			textLabel->textColor = 0xffcccccc;
		}
		{//存档重命名界面
			TextLabel* textLabel = new TextLabel(_T("重命名存档"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
			textLabel->setVisibleOperation(new OperationClass_Equal(VF_SaveRename), &visibleNum);
			textLabel->textColor = 0xffcccccc;
		}
	}
	Button* btnBack = new Button(gameData.btnSmall, _T("返回"), engine.g_pFont, DT_CENTER | DT_VCENTER);
	btnBack->setVisibleOperation(new OperationClass_AnyEqual(vector<int>{VF_Multiplayer, VF_Settings}), &visibleNum);
	btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackClicked);
	addWidget(btnBack);

	LineEdit* lineEdit1 = new LineEdit(engine.g_pFontSmall, TextAlign::Left, 350, 40, Align::Left | Align::Top);
	lineEdit1->text = _T("测试文字 a a");
	lineEdit1->move(50, 50);
	addWidget(lineEdit1);

	LineEdit* lineEdit2 = new LineEdit(engine.g_pFontSmall, TextAlign::Left, 350, 40, Align::Left | Align::Top);
	lineEdit2->text = _T("测试文字 aa                    ");
	lineEdit2->textColor = 0xffcc4444;
	lineEdit2->move(50, 100);
	addWidget(lineEdit2);

	LineEdit* lineEdit3 = new LineEdit(engine.g_pFontSmall, TextAlign::Left, 350, 40, Align::Left | Align::Top);
	lineEdit3->text = _T("测试文字 aa          ABCabc____");
	lineEdit3->move(50, 150);
	addWidget(lineEdit3);
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {
	engine.drawBorder(250, 250, 200, 200, 3, 0xff00ff00);

	Room::onRender();
}