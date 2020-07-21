#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

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

		Button* btnBack = new Button(gameData.btnSmall, _T("返回"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackClicked);
	}
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {

	Room::onRender();
}