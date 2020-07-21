#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;

Room_Title::Room_Title() {
	{//标题界面的按钮
		SC int offY = 40;

		Button* btnSigleplayer = new Button(gameData.btnBig, _T("单人游戏"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSigleplayer->move(0, -70 + offY);
		btnSigleplayer->setVisibleOperation(new OperationClass_Equal(0), &visibleNum);
		btnSigleplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnSigleplayerClicked);
		addWidget(btnSigleplayer);

		Button* btnMultiplayer = new Button(gameData.btnBig, _T("多人游戏"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnMultiplayer->move(0, offY);
		btnMultiplayer->setVisibleOperation(new OperationClass_Equal(0), &visibleNum);
		btnMultiplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnMultiplayerClicked);
		addWidget(btnMultiplayer);

		Button* btnSettings = new Button(gameData.btnBig, _T("设置"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSettings->move(0, 70 + offY);
		btnSettings->setVisibleOperation(new OperationClass_Equal(0), &visibleNum);
		btnSettings->setSlot(this, (ButtonFunc)&Room_Title::onBtnSettingsClicked);
		addWidget(btnSettings);

		Button* btnExit = new Button(gameData.btnBig, _T("退出"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnExit->move(0, 140 + offY);
		btnExit->setVisibleOperation(new OperationClass_Equal(0), &visibleNum);
		btnExit->setSlot(this, (ButtonFunc)&Room_Title::onBtnExitClicked);
		addWidget(btnExit);
	}
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {

	Room::onRender();
}