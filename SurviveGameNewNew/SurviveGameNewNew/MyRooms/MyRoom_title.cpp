#include "MyRoom_title.h"

using namespace std;

MyRoom_title* slotWidget = nullptr;

void btnSiglePressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSiglePressed(ev);
}
void btnMultiPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnMultiPressed(ev);
}
void btnSettingsPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSettingsPressed(ev);
}
void btnExitPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnExitPressed(ev);
}

void btnSigleJoinPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSigleJoinPressed(ev);
}
void btnSigleRenamePressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSigleRenamePressed(ev);
}
void btnSigleDeletePressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSigleDeletePressed(ev);
}
void btnSigleCreatePressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSigleCreatePressed(ev);
}
void btnSigleBackPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnSigleBackPressed(ev);
}

void btnCreateBackPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnCreateBackPressed(ev);
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
	MyTexture* textureSaveCreate = &guiTexture->guiSaveCreate;
	
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
		MyWidget* widget = new MyWidget(e, textureSaveSelect->g_pTexture, &textureSaveSelect->info);
		widget->visible = 1;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyTextWidget* textTitle = new MyTextWidget(e, widget->w, 20, e->g_pFontSmall, TEXT("选择存档"), nullptr, widget);
		textTitle->format = DT_CENTER | DT_VCENTER;
		textTitle->textColor = 0xffcccccc;
		textTitle->setAlign(AlignFlags::Top);

		MyPushButton* btnRename = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, btnSigleRenamePressed, nullptr, widget);
		btnRename->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnRename->move(88, 46);
		btnRename->text = stringToWstring("重命名");

		MyPushButton* btnDelete = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, btnSigleDeletePressed, nullptr, widget);
		btnDelete->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnDelete->move(5, 46);
		btnDelete->text = stringToWstring("删除");
		
		MyPushButton* btnJoin = new MyPushButton(e, textureBtnMedium->g_pTexture, &textureBtnMedium->info,
			e->g_pFont, btnSigleJoinPressed, nullptr, widget);
		btnJoin->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnJoin->move(5, 5);
		btnJoin->text = stringToWstring("进入");

		MyPushButton* btnCreate = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnSigleCreatePressed, nullptr, widget);
		btnCreate->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnCreate->move(175, 5);
		btnCreate->text = stringToWstring("新建");

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnSigleBackPressed, nullptr, widget);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = stringToWstring("返回");
	}

	//新建存档界面
	{
		MyWidget* widget = new MyWidget(e, textureSaveCreate->g_pTexture, &textureSaveCreate->info);
		widget->visible = 4;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnCreateBackPressed, nullptr, widget);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = stringToWstring("返回");
	}
}
MyRoom_title::~MyRoom_title() {}

void MyRoom_title::_onLogic() {
	
}
void MyRoom_title::_onRender() {
	
}
void MyRoom_title::_onDebug() {
	string str = "visible: " + to_string(visibleFlags);
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, nullptr, DT_LEFT | DT_TOP, 0xff000000);
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
		visibleFlags = 4;
	}
}
void MyRoom_title::_btnSigleBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 0;
	}
}

void MyRoom_title::_btnCreateBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 1;
	}
}