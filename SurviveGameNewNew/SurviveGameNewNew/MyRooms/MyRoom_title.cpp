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
void btnCreateAcceptPressed(MyMouseEvent ev) {
	if (slotWidget)
		slotWidget->_btnCreateAcceptPressed(ev);
}


MyRoom_title::MyRoom_title(MyEngine* e) : MyRoom(e) {
	slotWidget = this;
	this->e = e;
	//���ڿؼ�
	MyGuiTexture* guiTexture = &e->data.guiTexture;
	MyTexture* textureBtnVerySmall = &guiTexture->btnVerySmall;
	MyTexture* textureBtnSmall = &guiTexture->btnSmall;
	MyTexture* textureBtnMedium = &guiTexture->btnMedium;
	MyTexture* textureBtnBig = &guiTexture->btnBig;
	MyTexture* textureSaveSelect = &guiTexture->guiSaveSelect;
	MyTexture* textureSaveCreate = &guiTexture->guiSaveCreate;
	
	//�������
	{
		int offY = 40;
		MyPushButton* btnSigle = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSiglePressed);
		btnSigle->visible = 0;
		btnSigle->pVisible = &visibleFlags;
		btnSigle->move(0, -70 + offY);
		btnSigle->text = TEXT("������Ϸ");
		widgets.push_back(btnSigle);

		MyPushButton* btnMulti = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnMultiPressed);
		btnMulti->visible = 0;
		btnMulti->pVisible = &visibleFlags;
		btnMulti->move(0, offY);
		btnMulti->text = TEXT("������Ϸ(û��)");
		widgets.push_back(btnMulti);

		MyPushButton* btnSettings = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSettingsPressed);
		btnSettings->visible = 0;
		btnSettings->pVisible = &visibleFlags;
		btnSettings->move(0, 70 + offY);
		btnSettings->text = TEXT("����(û��)");
		widgets.push_back(btnSettings);

		MyPushButton* btnExit = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnExitPressed);
		btnExit->visible = 0;
		btnExit->pVisible = &visibleFlags;
		btnExit->move(0, 140 + offY);
		btnExit->text = TEXT("�˳�");
		widgets.push_back(btnExit);
	}

	//�浵ѡ�����
	{
		MyWidget* widget = new MyWidget(e, textureSaveSelect->g_pTexture, &textureSaveSelect->info);
		widget->visible = 1;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyTextWidget* title = new MyTextWidget(e, widget->w, 20, e->g_pFontSmall, TEXT("ѡ��浵"), nullptr, widget);
		title->format = DT_CENTER | DT_VCENTER;
		title->textColor = 0xffcccccc;
		title->setAlign(AlignFlags::Top);

		MyPushButton* btnRename = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, btnSigleRenamePressed, nullptr, widget);
		btnRename->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnRename->move(88, 46);
		btnRename->text = TEXT("������(û��)");

		MyPushButton* btnDelete = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info,
			e->g_pFontSmall, btnSigleDeletePressed, nullptr, widget);
		btnDelete->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnDelete->move(5, 46);
		btnDelete->text = TEXT("ɾ��(û��)");
		
		MyPushButton* btnJoin = new MyPushButton(e, textureBtnMedium->g_pTexture, &textureBtnMedium->info,
			e->g_pFont, btnSigleJoinPressed, nullptr, widget);
		btnJoin->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnJoin->move(5, 5);
		btnJoin->text = TEXT("����(û��)");

		MyPushButton* btnCreate = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnSigleCreatePressed, nullptr, widget);
		btnCreate->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnCreate->move(175, 5);
		btnCreate->text = TEXT("�½�");

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnSigleBackPressed, nullptr, widget);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = TEXT("����");
	}

	//�½��浵����
	{
		MyWidget* widget = new MyWidget(e, textureSaveCreate->g_pTexture, &textureSaveCreate->info);
		widget->visible = 4;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyTextWidget* title = new MyTextWidget(e, widget->w, 20, e->g_pFontSmall, TEXT("�½��浵"), nullptr, widget);
		title->format = DT_CENTER | DT_VCENTER;
		title->textColor = 0xffcccccc;
		title->setAlign(AlignFlags::Top);
		//24 22
		MyTextWidget* saveNameLeft = new MyTextWidget(e, 220, 22, e->g_pFontSmall, TEXT("�浵����"), nullptr, widget);
		saveNameLeft->format = DT_LEFT | DT_BOTTOM;
		saveNameLeft->textColor = 0xffffffff;
		saveNameLeft->setAlign(AlignFlags::Top);
		saveNameLeft->move(-110, 24);

		MyTextWidget* saveNameRight = new MyTextWidget(e, 220, 22, e->g_pFontSmall, TEXT("����:20���ַ�"), nullptr, widget);
		saveNameRight->format = DT_RIGHT | DT_BOTTOM;
		saveNameRight->textColor = 0xffffffff;
		saveNameRight->setAlign(AlignFlags::Top);
		saveNameRight->move(110, 24);

		editSaveName = new MyTextEdit(e, 440, 35, e->g_pFont, &focusWidget, widget);
		editSaveName->setAlign(AlignFlags::Top);
		editSaveName->move(0, 50);
		editSaveName->maxLength = 20;
		editSaveName->expr.setExpr(TEXT("\\/:*?\"<>|."), false);

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnCreateBackPressed, nullptr, widget);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = TEXT("����");

		MyPushButton* btnAccept = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info,
			e->g_pFont, btnCreateAcceptPressed, nullptr, widget);
		btnAccept->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnAccept->move(5, 5);
		btnAccept->text = TEXT("����");
	}
}
MyRoom_title::~MyRoom_title() {}

void MyRoom_title::_onLogic() {
	
}
void MyRoom_title::_onRender() {
	
}
void MyRoom_title::_onDebug() {
	string str = "visibleFlags: " + to_string(visibleFlags);
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
		editSaveName->clear();
		visibleFlags = 1;
	}
}
void MyRoom_title::_btnCreateAcceptPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		wstring saveName = editSaveName->text;
		wstring_trimmed(saveName);
		if (saveName != TEXT("")) {
			MyGlobal* global = &e->global;
			global->createSaveName = saveName;
			global->createSaveWidth = 8400;
			global->createSaveHeight = 2400;
			global->createSaveSeed = 114514;
			changeRoomStr = "createSave";
		}
	}
}