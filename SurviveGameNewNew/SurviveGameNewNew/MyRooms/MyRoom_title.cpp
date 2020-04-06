#include "MyRoom_title.h"

using namespace std;

MyRoom_title* slotWidget = nullptr;

void btnSiglePressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSiglePressed(mouse);
}
void btnMultiPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnMultiPressed(mouse);
}
void btnSettingsPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSettingsPressed(mouse);
}
void btnExitPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnExitPressed(mouse);
}

void btnSigleJoinPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSigleJoinPressed(mouse);
}
void btnSigleRenamePressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSigleRenamePressed(mouse);
}
void btnSigleDeletePressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSigleDeletePressed(mouse);
}
void btnSigleCreatePressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSigleCreatePressed(mouse);
}
void btnSigleBackPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSigleBackPressed(mouse);
}

MyRoom_title::MyRoom_title(MyEngine* e) : MyRoom(e) {
	slotWidget = this;
	this->e = e;
	//窗口控件
	MyGuiTexture* guiTexture = &e->data.guiTexture;
	MyTexture* textureBtnVerySmall = &guiTexture->btnVerySmall;
	MyTexture* textureBtnSmall = &guiTexture->btnSmall;
	MyTexture* textureBtnMedium = &guiTexture->btnMedium;
	MyTexture* textureBtnBig = &guiTexture->btnBig;
	MyTexture* textureSaveSelect = &guiTexture->guiSaveSelect;

	//标题界面
	{
		int offY = 40;
		MyPushButton* btnSigle = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSiglePressed);
		btnSigle->visible = 0;
		btnSigle->pVisible = &visibleFlags;
		btnSigle->move(0, -70 + offY);
		btnSigle->text = stringToWstring("单人游戏");
		widgets.push_back(btnSigle);

		MyPushButton* btnMulti = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnMultiPressed);
		btnMulti->visible = 0;
		btnMulti->pVisible = &visibleFlags;
		btnMulti->move(0, offY);
		btnMulti->text = stringToWstring("多人游戏(没做)");
		widgets.push_back(btnMulti);

		MyPushButton* btnSettings = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSettingsPressed);
		btnSettings->visible = 0;
		btnSettings->pVisible = &visibleFlags;
		btnSettings->move(0, 70 + offY);
		btnSettings->text = stringToWstring("设置(没做)");
		widgets.push_back(btnSettings);

		MyPushButton* btnExit = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnExitPressed);
		btnExit->visible = 0;
		btnExit->pVisible = &visibleFlags;
		btnExit->move(0, 140 + offY);
		btnExit->text = stringToWstring("退出");
		widgets.push_back(btnExit);
	}

	//存档选择界面
	{
		MyWidget* widgetSaveSelect = new MyWidget(e, textureSaveSelect->g_pTexture, &textureSaveSelect->info);
		widgetSaveSelect->visible = 1;
		widgetSaveSelect->pVisible = &visibleFlags;
		widgets.push_back(widgetSaveSelect);

		MyPushButton* btnSigleRename = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, nullptr, nullptr, widgetSaveSelect);
		btnSigleRename->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnSigleRename->move(88, 46);
		btnSigleRename->text = stringToWstring("重命名");

		MyPushButton* btnSigleDelete = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, nullptr, nullptr, widgetSaveSelect);
		btnSigleDelete->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnSigleDelete->move(5, 46);
		btnSigleDelete->text = stringToWstring("删除");

		MyPushButton* btnSigleJoin = new MyPushButton(e, textureBtnMedium->g_pTexture, &textureBtnMedium->info,
			e->g_pFont, nullptr, nullptr, widgetSaveSelect);
		btnSigleJoin->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnSigleJoin->move(5, 5);
		btnSigleJoin->text = stringToWstring("进入");

		MyPushButton* btnSigleCreate = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, nullptr, nullptr, widgetSaveSelect);
		btnSigleCreate->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnSigleCreate->move(175, 5);
		btnSigleCreate->text = stringToWstring("新建");

		MyPushButton* btnSigleBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnSigleBackPressed, nullptr, widgetSaveSelect);
		btnSigleBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnSigleBack->move(5, 5);
		btnSigleBack->text = stringToWstring("返回");
	}

}
MyRoom_title::~MyRoom_title() {}

void MyRoom_title::_onLogic() {
	
}
void MyRoom_title::_onRender() {

}
void MyRoom_title::_onDebug() {

}

void MyRoom_title::_onDestroy() {

}

void MyRoom_title::_btnSiglePressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		visibleFlags = 1;
	}
}
void MyRoom_title::_btnMultiPressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		//visibleFlags = 2;
	}
}
void MyRoom_title::_btnSettingsPressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		//visibleFlags = 3;
	}
}
void MyRoom_title::_btnExitPressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		SendMessage(e->g_hWnd, WM_CLOSE, 0, 0);
	}
}

void MyRoom_title::_btnSigleJoinPressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		
	}
}
void MyRoom_title::_btnSigleRenamePressed(int mouse) {
	if (mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::_btnSigleDeletePressed(int mouse) {
	if (mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::_btnSigleCreatePressed(int mouse) {
	if (mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::_btnSigleBackPressed(int mouse) {
	if (mouse == VK_LBUTTON) {
		visibleFlags = 0;
	}
}
