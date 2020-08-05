#include "RoomTitle.h"

#include "../Engine/Engine.h"

using namespace My;
using namespace std;

Room_Title::Room_Title() {
	visibleNum = VF_Title;

	wstring arr[]{ _T("TESSSS"), _T("DFABH"), _T("YOYOSB") };
	for (wstring wstr : arr) {
		SaveInfo si;
		si.saveName = si.saveNameInFile = wstr;
		si.seed = rand() % 1003;
		si.time = time(nullptr);
		si.save();
		si.load(wstr);
	}
	{//�������
		SC int offY = 40;

		Button* btnSigleplayer = new Button(gameData.btnBig, _T("������Ϸ"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSigleplayer->move(0, -70 + offY);
		btnSigleplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSigleplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnSigleplayerClicked);
		addWidget(btnSigleplayer);

		Button* btnMultiplayer = new Button(gameData.btnBig, _T("������Ϸ(û��)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnMultiplayer->move(0, offY);
		btnMultiplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnMultiplayer->setSlot(this, (ButtonFunc)&Room_Title::onBtnMultiplayerClicked);
		addWidget(btnMultiplayer);

		Button* btnSettings = new Button(gameData.btnBig, _T("����(û��)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSettings->move(0, 70 + offY);
		btnSettings->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSettings->setSlot(this, (ButtonFunc)&Room_Title::onBtnSettingsClicked);
		addWidget(btnSettings);

		Button* btnExit = new Button(gameData.btnBig, _T("�˳�"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnExit->move(0, 140 + offY);
		btnExit->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnExit->setSlot(this, (ButtonFunc)&Room_Title::onBtnExitClicked);
		addWidget(btnExit);
	}
	{//�浵ѡ�����
		ImageLabel* widget = new ImageLabel(gameData.saveSelect);
		widget->setVisibleOperation(new OperationClass_Equal(VF_SaveSelect), &visibleNum);
		addWidget(widget);

		TextLabel* textLabel = new TextLabel(_T("ѡ��浵"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
		textLabel->textColor = 0xffcccccc;

		Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackClicked);

		Button* btnCreate = new Button(gameData.btnSmall, _T("�½�"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnCreate->move(175, 5);
		btnCreate->setSlot(this, (ButtonFunc)&Room_Title::onBtnCreateClicked);

		selectSaveMenu.btnJoin = new Button(gameData.btnMedium, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnJoin->isEnabled = false;
		selectSaveMenu.btnJoin->move(5, 5);
		selectSaveMenu.btnJoin->setSlot(this, (ButtonFunc)&Room_Title::onBtnSigleplayerJoinClicked);

		selectSaveMenu.btnRename = new Button(gameData.btnVerySmall, _T("������"), engine.g_pFontVerySmall,
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnRename->isEnabled = false;
		selectSaveMenu.btnRename->move(88, 46);
		selectSaveMenu.btnRename->setSlot(this, (ButtonFunc)&Room_Title::onBtnRenameClicked);

		selectSaveMenu.btnDelete = new Button(gameData.btnVerySmall, _T("ɾ��"), engine.g_pFontVerySmall,
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnDelete->isEnabled = false;
		selectSaveMenu.btnDelete->move(5, 46);
		selectSaveMenu.btnDelete->setSlot(this, (ButtonFunc)&Room_Title::onBtnSaveDeleteClicked);
	}
	{//�浵�������� /ͬʱҲ�Ǵ浵����������
		ImageLabel* widget = new ImageLabel(gameData.saveCreate);
		widget->setVisibleOperation(new OperationClass_AnyEqual({VF_SaveCreate, VF_SaveRename}), &visibleNum);
		addWidget(widget);

		Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackToSelectClicked);

		TextLabel* saveNameLeft = new TextLabel(_T("�浵����"), engine.g_pFontVerySmall, DT_LEFT | DT_BOTTOM, 220, 22, Align::Top, widget);
		saveNameLeft->textColor = 0xffffffff;
		saveNameLeft->move(-110, 24);

		TextLabel* saveNameRight = new TextLabel(_T("����:35���ַ�"), engine.g_pFontVerySmall, DT_RIGHT | DT_BOTTOM, 220, 22, Align::Top, widget);
		saveNameRight->textColor = 0xffffffff;
		saveNameRight->move(110, 24);

		selectSaveMenu.saveNameEdit = new LineEdit(engine.g_pFontSmall, TextAlign::Scroll, 440, 35, Align::Top, widget);
		selectSaveMenu.saveNameEdit->move(0, 50);
		selectSaveMenu.saveNameEdit->maxLength = 35;
		selectSaveMenu.saveNameEdit->textRegex = new regex("[^\\\\/:\\*?\"<>\\|\\.]*");

		{//�浵��������
			TextLabel* textLabel = new TextLabel(_T("�����浵"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
			textLabel->setVisibleOperation(new OperationClass_Equal(VF_SaveCreate), &visibleNum);
			textLabel->textColor = 0xffcccccc;

			Button* btnAccept = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
			btnAccept->move(5, 5);
			btnAccept->setSlot(this, (ButtonFunc)&Room_Title::onBtnCreateAcceptClicked);
		}
		{//�浵����������
			TextLabel* textLabel = new TextLabel(_T("�������浵"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
			textLabel->setVisibleOperation(new OperationClass_Equal(VF_SaveRename), &visibleNum);
			textLabel->textColor = 0xffcccccc;

			Button* btnAccept = new Button(gameData.btnSmall, _T("ȷ��"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
			btnAccept->move(5, 5);
			btnAccept->setSlot(this, (ButtonFunc)&Room_Title::onBtnRenameAcceptClicked);
		}
	}
	Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER);
	btnBack->setVisibleOperation(new OperationClass_AnyEqual(vector<int>{VF_Multiplayer, VF_Settings}), &visibleNum);
	btnBack->setSlot(this, (ButtonFunc)&Room_Title::onBtnBackClicked);
	addWidget(btnBack);
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {
	
	Room::onRender();
}


void Room_Title::setVisibleNum(int num) {
	switch (num) {
	case VF_SaveCreate:
	case VF_SaveRename:
		selectSaveMenu.saveNameEdit->text = _T("");
		break;
	}

	Room::setVisibleNum(num);
}


void Room_Title::onBtnCreateAcceptClicked(AbstractButton*) {
	setVisibleNum(VF_SaveSelect);
}

void Room_Title::onBtnRenameAcceptClicked(AbstractButton*) {
	setVisibleNum(VF_SaveSelect);
}