#include "MyRoom_title.h"

using namespace std;

MyRoom_title* slotWidget = nullptr;

void btnSiglePressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSiglePressed(ev);
}
void btnMultiPressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnMultiPressed(ev);
}
void btnSettingsPressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSettingsPressed(ev);
}
void btnExitPressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnExitPressed(ev);
}

void btnSigleJoinPressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSigleJoinPressed(ev);
}
void btnSigleRenamePressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSigleRenamePressed(ev);
}
void btnSigleDeletePressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSigleDeletePressed(ev);
}
void btnSigleCreatePressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSigleCreatePressed(ev);
}
void btnSigleBackPressed(MyMouseEvent ev) {
	if (slotWidget && ev.type == MouseFlags::Press)
		slotWidget->_btnSigleBackPressed(ev);
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

		MyTextEdit* textEdit = new MyTextEdit(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, &focusWidget, widgetSaveSelect);
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

void MyRoom_title::_btnSiglePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 1;
	}
}
void MyRoom_title::_btnMultiPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		//visibleFlags = 2;
	}
}
void MyRoom_title::_btnSettingsPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		//visibleFlags = 3;
	}
}
void MyRoom_title::_btnExitPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		SendMessage(e->g_hWnd, WM_CLOSE, 0, 0);
	}
}

void MyRoom_title::_btnSigleJoinPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		
	}
}
void MyRoom_title::_btnSigleRenamePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::_btnSigleDeletePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::_btnSigleCreatePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		
	}
}
void MyRoom_title::_btnSigleBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 0;
	}
}
