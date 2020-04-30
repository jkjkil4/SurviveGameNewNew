#include "MyRoom_title.h"

using namespace std;


MyRoom_title::MyRoom_title(MyEngine* e) : MyRoom(e) {
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
		MyPushButton* btnSigle = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont);
		btnSigle->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSiglePressed), this);
		btnSigle->visible = 0;
		btnSigle->pVisible = &visibleFlags;
		btnSigle->move(0, -70 + offY);
		btnSigle->text = TEXT("单人游戏");
		widgets.push_back(btnSigle);
		
		MyPushButton* btnMulti = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont);
		btnMulti->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnMultiPressed), this);
		btnMulti->visible = 0;
		btnMulti->pVisible = &visibleFlags;
		btnMulti->move(0, offY);
		btnMulti->text = TEXT("多人游戏(没做)");
		widgets.push_back(btnMulti);

		MyPushButton* btnSettings = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont);
		btnSettings->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSettingsPressed), this);
		btnSettings->visible = 0;
		btnSettings->pVisible = &visibleFlags;
		btnSettings->move(0, 70 + offY);
		btnSettings->text = TEXT("设置(没做)");
		widgets.push_back(btnSettings);

		MyPushButton* btnExit = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont);
		btnExit->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnExitPressed), this);
		btnExit->visible = 0;
		btnExit->pVisible = &visibleFlags;
		btnExit->move(0, 140 + offY);
		btnExit->text = TEXT("退出");
		widgets.push_back(btnExit);
	}

	//存档选择界面
	{
		MyWidget* widget = new MyWidget(e, textureSaveSelect->g_pTexture, &textureSaveSelect->info);
		widget->visible = 1;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyTextWidget* title = new MyTextWidget(e, widget->w, 20, e->g_pFontVerySmall, TEXT("选择存档"), nullptr, widget);
		title->format = DT_CENTER | DT_VCENTER;
		title->textColor = 0xffcccccc;
		title->setAlign(AlignFlags::Top);

		scrView = new MyScrollView(e, 412, 440, widget);
		scrView->setAlign(AlignFlags::Left | AlignFlags::Top);
		scrView->move(9, 30);
		scrView->childH = saveWidgetHeight;

		saveInfoWidget = new MyTextWidget(e, 159, 276, e->g_pFontVerySmall, TEXT(""), nullptr, widget);
		saveInfoWidget->setAlign(AlignFlags::Right | AlignFlags::Top);
		saveInfoWidget->move(7, 168);
		saveInfoWidget->format = DT_LEFT | DT_TOP;
		saveInfoWidget->textColor = 0xffffffff;

		MyPushButton* btnRename = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info, e->g_pFontVerySmall, widget);
		btnRename->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSigleRenamePressed), this);
		btnRename->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnRename->move(88, 46);
		btnRename->text = TEXT("重命名(没做)");

		MyPushButton* btnDelete = new MyPushButton(e, textureBtnVerySmall->g_pTexture, &textureBtnVerySmall->info, e->g_pFontVerySmall, widget);
		btnDelete->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSigleDeletePressed), this);
		btnDelete->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnDelete->move(5, 46);
		btnDelete->text = TEXT("删除(没做)");
		
		MyPushButton* btnJoin = new MyPushButton(e, textureBtnMedium->g_pTexture, &textureBtnMedium->info, e->g_pFont, widget);
		btnJoin->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSigleJoinPressed), this);
		btnJoin->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnJoin->move(5, 5);
		btnJoin->text = TEXT("进入");

		MyPushButton* btnCreate = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info, e->g_pFont, widget);
		btnCreate->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSigleCreatePressed), this);
		btnCreate->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnCreate->move(175, 5);
		btnCreate->text = TEXT("新建");

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info, e->g_pFont, widget);
		btnBack->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnSigleBackPressed), this);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = TEXT("返回");
	}

	//新建存档界面
	{
		MyWidget* widget = new MyWidget(e, textureSaveCreate->g_pTexture, &textureSaveCreate->info);
		widget->visible = 4;
		widget->pVisible = &visibleFlags;
		widgets.push_back(widget);

		MyTextWidget* title = new MyTextWidget(e, widget->w, 20, e->g_pFontVerySmall, TEXT("新建存档"), nullptr, widget);
		title->format = DT_CENTER | DT_VCENTER;
		title->textColor = 0xffcccccc;
		title->setAlign(AlignFlags::Top);
		//24 22
		MyTextWidget* saveNameLeft = new MyTextWidget(e, 220, 22, e->g_pFontVerySmall, TEXT("存档名称"), nullptr, widget);
		saveNameLeft->format = DT_LEFT | DT_BOTTOM;
		saveNameLeft->textColor = 0xffffffff;
		saveNameLeft->setAlign(AlignFlags::Top);
		saveNameLeft->move(-110, 24);

		MyTextWidget* saveNameRight = new MyTextWidget(e, 220, 22, e->g_pFontVerySmall, TEXT("限制:20个字符"), nullptr, widget);
		saveNameRight->format = DT_RIGHT | DT_BOTTOM;
		saveNameRight->textColor = 0xffffffff;
		saveNameRight->setAlign(AlignFlags::Top);
		saveNameRight->move(110, 24);

		editSaveName = new MyTextEdit(e, 440, 35, e->g_pFont, &focusWidget, widget);
		editSaveName->setAlign(AlignFlags::Top);
		editSaveName->move(0, 50);
		editSaveName->maxLength = 20;
		editSaveName->expr.setExpr(TEXT("\\/:*?\"<>|."), false);

		MyPushButton* btnBack = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info, e->g_pFont, widget);
		btnBack->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnCreateBackPressed), this);
		btnBack->setAlign(AlignFlags::Left | AlignFlags::Bottom);
		btnBack->move(5, 5);
		btnBack->text = TEXT("返回");

		MyPushButton* btnAccept = new MyPushButton(e, textureBtnSmall->g_pTexture, &textureBtnSmall->info, e->g_pFont, widget);
		btnAccept->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_title::btnCreateAcceptPressed), this);
		btnAccept->setAlign(AlignFlags::Right | AlignFlags::Bottom);
		btnAccept->move(5, 5);
		btnAccept->text = TEXT("创建");
	}

	if (visibleFlags == 1)
		loadSavesList();
	e->global.reset();
}

void MyRoom_title::_onLogic() {
	if (tmpSave != shownSave) {
		if (shownSave) {
			MySave::Info* info = shownSave->info;
			tm* ltm = localtime(&info->time);
			wstring timeMinStr = to_wstring(ltm->tm_min);
			if (timeMinStr.length() == 1)
				timeMinStr.insert(timeMinStr.begin(), TEXT('0'));
			wstring timeStr = to_wstring(1900 + ltm->tm_year) + TEXT("年") + to_wstring(1 + ltm->tm_mon) + TEXT("月")
				+ to_wstring(ltm->tm_mday) + TEXT("日 ") + to_wstring(ltm->tm_hour) + TEXT(":") + timeMinStr;

			saveInfoWidget->text = 
				  TEXT("名称: ") + info->name	//存档名称
				+ TEXT("\n\n时间: ") + timeStr	//存档时间
				+ TEXT("\n种子: ") + to_wstring(info->seed)		//种子
				+ TEXT("\n大小: ") + to_wstring(info->width) + TEXT("x") + to_wstring(info->height);		//大小
		}
		tmpSave = shownSave;
	}
}
void MyRoom_title::_onRender() {
	
}
void MyRoom_title::_onDebug() {
	string str = "visibleFlags: " + to_string(visibleFlags) +
		"\nFPS: " + to_string(*e->fps);
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, nullptr, DT_LEFT | DT_TOP, 0xff000000);
}

void MyRoom_title::_onDestroy() {
	for (auto it = saves.begin(); it < saves.end(); it++)
		safeDelete(*it);
}


void MyRoom_title::loadSavesList() {
	//销毁
	for (auto it = saves.begin(); it < saves.end(); it++)
		safeDelete(*it);
	saves.clear();
	scrView->clear();
	saveInfoWidget->text = TEXT("");
	tmpSave = nullptr;
	shownSave = nullptr;
	//读取
	vector<wstring> files;
	MyDir::entryList(TEXT("data\\saves\\"), &files, MyDir::Dir);
	for (auto it = files.begin(); it < files.end(); it++) {
		MySave* save = new MySave;
		wstring path = TEXT("data\\saves\\") + *it + TEXT("\\saveInfo");
		if (!save->loadInfo(path)) {
			safeDelete(save);
			continue;
		}
		bool isAccepted = false;
		for (auto it = saves.begin(); it < saves.end(); it++) {
			time_t timeCheck = (*it)->info->time;
			if (save->info->time > timeCheck) {
				saves.insert(it, save);
				isAccepted = true;
				break;
			}
		}
		if (!isAccepted)
			saves.push_back(save);
	}
	//创建控件     412 438
	for (auto it = saves.begin(); it < saves.end(); it++) {
		MySaveWidget* saveWidget = new MySaveWidget(e, 412, saveWidgetHeight, *it, e->g_pFontSmall, e->g_pFontVerySmall, scrView);
		saveWidget->setAlign(AlignFlags::Top | AlignFlags::Left);
		saveWidget->shownSave = &shownSave;
		saveWidget->color = D3DCOLOR_XRGB(66, 66, 128);
		saveWidget->selColor = D3DCOLOR_XRGB(54, 54, 113);
		saveWidget->textColor = 0xffffffff;
	}
	scrView->updateChildsPos();
}


void MyRoom_title::btnSiglePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		loadSavesList();
		visibleFlags = 1;
	}
}
void MyRoom_title::btnMultiPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		//visibleFlags = 2;
	}
}
void MyRoom_title::btnSettingsPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		//visibleFlags = 3;
	}
}
void MyRoom_title::btnExitPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		sendMessage = WM_CLOSE;
	}
}

void MyRoom_title::btnSigleJoinPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		if (shownSave) {
			e->global.loadSave = new MyGlobal::LoadSave(TEXT("data\\saves\\") + shownSave->info->name);
			setChangeRoomStr("loadSave");
		}
	}
}
void MyRoom_title::btnSigleRenamePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::btnSigleDeletePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {

	}
}
void MyRoom_title::btnSigleCreatePressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 4;
	}
}
void MyRoom_title::btnSigleBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		visibleFlags = 0;
	}
}

void MyRoom_title::btnCreateBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		editSaveName->clear();
		loadSavesList();
		visibleFlags = 1;
	}
}
void MyRoom_title::btnCreateAcceptPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		wstring saveName = editSaveName->text;
		wstring_trimmed(saveName);
		if (saveName != TEXT("")) {
			e->global.createSave = new MyGlobal::CreateSave(saveName, 400, 400, 114514);
			setChangeRoomStr("createSave");
		}
	}
}