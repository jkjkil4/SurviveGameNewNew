#include "Room_Title.h"

//#include "../Engine/Engine.h"

#include "Room_CreateSave.h"

using namespace My;
using namespace std;

Room_Title::Room_Title(int visibleNum_) {
	{//�������
		SC int offY = 40;

		Button* btnSingleplayer = new Button(gameData.btnBig, _T("������Ϸ"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSingleplayer->move(0, -70 + offY);
		btnSingleplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSingleplayer->setSlot(this, (ButtonSlot)&Room_Title::onBtnSingleplayerClicked);
		addWidget(btnSingleplayer);

		Button* btnMultiplayer = new Button(gameData.btnBig, _T("������Ϸ(û��)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnMultiplayer->move(0, offY);
		btnMultiplayer->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnMultiplayer->setSlot(this, (ButtonSlot)&Room_Title::onBtnMultiplayerClicked);
		addWidget(btnMultiplayer);

		Button* btnSettings = new Button(gameData.btnBig, _T("����(û��)"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnSettings->move(0, 70 + offY);
		btnSettings->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnSettings->setSlot(this, (ButtonSlot)&Room_Title::onBtnSettingsClicked);
		addWidget(btnSettings);

		Button* btnExit = new Button(gameData.btnBig, _T("�˳�"), engine.g_pFont, DT_CENTER | DT_VCENTER);
		btnExit->move(0, 140 + offY);
		btnExit->setVisibleOperation(new OperationClass_Equal(VF_Title), &visibleNum);
		btnExit->setSlot(this, (ButtonSlot)&Room_Title::onBtnExitClicked);
		addWidget(btnExit);
	}
	{//�浵ѡ�����
		ImageLabel* widget = new ImageLabel(gameData.saveSelect);
		widget->setVisibleOperation(new OperationClass_Equal(VF_SaveSelect), &visibleNum);
		addWidget(widget);

		TextLabel* textLabel = new TextLabel(_T("ѡ��浵"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
		textLabel->textColor = 0xffcccccc;

		selectSaveMenu.saveListWidget = new ListWidget(412, 442, Align::Left | Align::Top, widget);
		selectSaveMenu.saveListWidget->move(9, 29);
		selectSaveMenu.saveListWidget->margin = 0;
		selectSaveMenu.saveListWidget->canBtnBeFocused = true;
		selectSaveMenu.saveListWidget->setClickedSlot(this, (ListWidgetSlot)&Room_Title::onSaveListClicked);

		selectSaveMenu.saveInfoWidget = new TextLabel(_T(""), engine.g_pFontVerySmall, DT_LEFT | DT_TOP, 159, 276, Align::Right | Align::Top, widget);
		selectSaveMenu.saveInfoWidget->move(7, 168);
		selectSaveMenu.saveInfoWidget->textColor = 0xffffffff;

		Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonSlot)&Room_Title::onBtnBackClicked);

		Button* btnCreate = new Button(gameData.btnSmall, _T("�½�"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		btnCreate->move(175, 5);
		btnCreate->setSlot(this, (ButtonSlot)&Room_Title::onBtnCreateClicked);

		selectSaveMenu.btnJoin = new Button(gameData.btnMedium, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnJoin->isEnabled = false;
		selectSaveMenu.btnJoin->move(5, 5);
		selectSaveMenu.btnJoin->setSlot(this, (ButtonSlot)&Room_Title::onBtnSingleplayerJoinClicked);

		selectSaveMenu.btnRename = new Button(gameData.btnVerySmall, _T("������"), engine.g_pFontVerySmall,
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnRename->isEnabled = false;
		selectSaveMenu.btnRename->move(88, 46);
		selectSaveMenu.btnRename->setSlot(this, (ButtonSlot)&Room_Title::onBtnRenameClicked);

		selectSaveMenu.btnDelete = new Button(gameData.btnVerySmall, _T("ɾ��"), engine.g_pFontVerySmall,
			DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
		selectSaveMenu.btnDelete->isEnabled = false;
		selectSaveMenu.btnDelete->move(5, 46);
		selectSaveMenu.btnDelete->setSlot(this, (ButtonSlot)&Room_Title::onBtnSaveDeleteClicked);
	}
	{//�浵�������� /ͬʱҲ�Ǵ浵����������
		ImageLabel* widget = new ImageLabel(gameData.saveCreate);
		widget->setVisibleOperation(new OperationClass_AnyEqual({VF_SaveCreate, VF_SaveRename}), &visibleNum);
		addWidget(widget);

		Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, widget);
		btnBack->move(5, 5);
		btnBack->setSlot(this, (ButtonSlot)&Room_Title::onBtnBackToSelectClicked);

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
			btnAccept->setVisibleOperation(new OperationClass_Equal(VF_SaveCreate), &visibleNum);
			btnAccept->move(5, 5);
			btnAccept->setSlot(this, (ButtonSlot)&Room_Title::onBtnCreateAcceptClicked);
		}
		{//�浵����������
			TextLabel* textLabel = new TextLabel(_T("�������浵"), engine.g_pFontVerySmall, DT_CENTER | DT_VCENTER, widget->w, 20, Align::Top, widget);
			textLabel->setVisibleOperation(new OperationClass_Equal(VF_SaveRename), &visibleNum);
			textLabel->textColor = 0xffcccccc;

			Button* btnAccept = new Button(gameData.btnSmall, _T("ȷ��"), engine.g_pFont, DT_CENTER | DT_VCENTER, Align::Right | Align::Bottom, widget);
			btnAccept->setVisibleOperation(new OperationClass_Equal(VF_SaveRename), &visibleNum);
			btnAccept->move(5, 5);
			btnAccept->setSlot(this, (ButtonSlot)&Room_Title::onBtnRenameAcceptClicked);
		}
	}
	//�浵ɾ������
	{
		list<wstring> lButtons;
		lButtons.push_back(_T("ȡ��"));
		lButtons.push_back(_T("ȷ��"));
		deleteSaveMsgBox = new MsgBox(_T("ɾ���浵"), engine.g_pFontVerySmall, _T("ȷ��Ҫɾ����"), engine.g_pFontSmall, lButtons,
			gameData.btnSmall, engine.g_pFont, 300, 200);
		deleteSaveMsgBox->setVisibleOperation(new OperationClass_Equal(VF_SaveDelete), &visibleNum);
		deleteSaveMsgBox->setSlot(this, (MsgBoxSlot)&Room_Title::onBtnSaveDeleteBack);
		
		addWidget(deleteSaveMsgBox);
	}
	Button* btnBack = new Button(gameData.btnSmall, _T("����"), engine.g_pFont, DT_CENTER | DT_VCENTER);
	btnBack->setVisibleOperation(new OperationClass_AnyEqual(vector<int>{VF_Multiplayer, VF_Settings}), &visibleNum);
	btnBack->setSlot(this, (ButtonSlot)&Room_Title::onBtnBackClicked);
	addWidget(btnBack);

	setVisibleNum(visibleNum_);
}

void Room_Title::onLogic() {

	Room::onLogic();
}

void Room_Title::onRender() {
	
	Room::onRender();
}

void Room_Title::onDestroy() {
	selectSaveMenu.saveListWidget->clearItem();

	Room::onDestroy();
}


void Room_Title::setVisibleNum(int num) {
	switch (num) {
	case VF_SaveSelect: {
		ListWidget* saveListWidget = selectSaveMenu.saveListWidget;
		//����ԭ�ȵĶ���
		saveListWidget->clearItem();
		selectSaveMenu.saveInfoWidget->text = _T("");
		selectSaveMenu.btnJoin->isEnabled = false;
		selectSaveMenu.btnDelete->isEnabled = false;
		selectSaveMenu.btnRename->isEnabled = false;
		//�õ��浵�ļ��б�
		vector<wstring> saves;
		Dir::entryList(_T("data/saves"), &saves, nullptr);
		//��ȡ�浵��Ϣ
		for (wstring& save : saves) {
			saveListWidget->addItem(new SaveListItem(save));
		}
		//����
		sort(saveListWidget->vItems.begin(), saveListWidget->vItems.end(), 
			[](ListWidgetItem* a, ListWidgetItem* b) -> bool { 
				return ((SaveListItem*)a)->info.time > ((SaveListItem*)b)->info.time;
			});
		break;
	}
	case VF_SaveCreate:
	case VF_SaveRename:
		selectSaveMenu.saveNameEdit->text = _T("");
		break;
	}

	Room::setVisibleNum(num);
}


bool Room_Title::isSaveNameRight(const std::wstring& name) {
	return name.length() != 0 && *name.begin() != _T(' ') && *name.rbegin() != _T(' ');
}


void Room_Title::onBtnCreateAcceptClicked(AbstractButton*) {
	wstring saveName = strTrimmed(selectSaveMenu.saveNameEdit->text);
	if (!isSaveNameRight(saveName))
		return;
	if(!Dir::isExists(_T("data/saves/") + saveName))
		throw RoomGoto(new Room_CreateSave(saveName));
	
}

void Room_Title::onBtnRenameAcceptClicked(AbstractButton*) {
	setVisibleNum(VF_SaveSelect);
}

void Room_Title::onBtnSaveDeleteClicked(AbstractButton*) {
	SaveListItem* item = (SaveListItem*)selectSaveMenu.saveListWidget->getFocusedItem();
	deleteSaveMsgBox->text = _T("ȷ��Ҫɾ�� \n") + item->info.saveName + _T(" ��\nɾ���Ĵ浵�޷��ָ�");

	setVisibleNum(VF_SaveDelete);
}

void Room_Title::onBtnSaveDeleteBack(int index) {
	if (index == 1) {
		SaveListItem* item = (SaveListItem*)selectSaveMenu.saveListWidget->getFocusedItem();
		if (item->info.saveName.length() != 0) {
			Dir::removeDirectory(_T("data/saves/") + item->info.saveName);
		}
	}

	setVisibleNum(VF_SaveSelect);
}


void Room_Title::onSaveListClicked(ListWidgetItem* item) {
	SaveListItem* sItem = (SaveListItem*)item;
	SaveInfo& si = sItem->info;

	tm* ltm = localtime(&si.time);
	wstring timeMinStr = to_wstring(ltm->tm_min);
	if (timeMinStr.length() == 1)
		timeMinStr.insert(timeMinStr.begin(), TEXT('0'));
	wstring timeStr = to_wstring(1900 + ltm->tm_year) + TEXT("��") + to_wstring(1 + ltm->tm_mon) + TEXT("��")
		+ to_wstring(ltm->tm_mday) + TEXT("�� ") + to_wstring(ltm->tm_hour) + TEXT(":") + timeMinStr;

	selectSaveMenu.saveInfoWidget->text 
		= _T("����: ") + si.saveName
		+ _T("\n\nʱ��: ") + timeStr
		+ _T("\n����: ") + to_wstring(si.seed);

	selectSaveMenu.btnJoin->isEnabled = true;
	selectSaveMenu.btnDelete->isEnabled = true;
	selectSaveMenu.btnRename->isEnabled = true;
}