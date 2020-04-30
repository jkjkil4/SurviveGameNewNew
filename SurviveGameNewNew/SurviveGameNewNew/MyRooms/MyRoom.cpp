#include "MyRoom.h"

using namespace std;

MyRoom::MyRoom(MyEngine* e) {
	this->e = e;
	visibleFlags = e->global.visibleFlag;
}

void MyRoom::onBeforeKeyCheck() {
	if (focusWidget) {
		for (auto it = e->vec_keyBuffer.begin(); it < e->vec_keyBuffer.end(); it++) {
			MyKey* key = *it;
			int vk = key->key;
			if (key->flag) {	//���°���
				focusWidget->keyboardEvent(vk);
			}
		}
	}
}

string MyRoom::getChangeRoomStr() {
	e->changeRoomMutex.lock();
	string str = changeRoomStr;
	e->changeRoomMutex.unlock();
	return str;
}
void MyRoom::setChangeRoomStr(string str) {
	e->changeRoomMutex.lock();
	changeRoomStr = str;
	e->changeRoomMutex.unlock();
}

void MyRoom::onLogic() {
	//��Ӧ�����ַ�
	wstring wstr = e->inputWString;
	e->inputWString = TEXT("");
	if (focusWidget && wstr != TEXT("")) {
		focusWidget->charEvent(wstr);
	}
	
	//������
	if (e->wheelDelta != 0) {
		for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
			MyWidget* w = *it;
			if (!w->isVisible())
				continue;
			int localX = e->mouseX - w->realX;
			int localY = e->mouseY - w->realY;
			if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
				w->wheelEvent(localX, localY, e->wheelDelta);
				break;
			}
		}
		e->wheelDelta = 0;
	}

	//�ؼ��¼�
	const int* mice = e->mice;
	for (int i = 0; i < 3; i++) {
		int mouse = mice[i];
		if (e->keyPressFlag(mouse)) {
			if (mouseWidget) {
				mouseWidget->mouseEvent(MyMouseEvent(Press, mouse, e->mouseX - mouseWidget->wndX, e->mouseY - mouseWidget->wndY));
				e->setKeyPressFlag(mouse, false);
				if (mouse == VK_LBUTTON)
					focusWidget = mouseWidget;
			}
			else {
				if (mouse == VK_LBUTTON)
					focusWidget = nullptr;
			}
		}
		if (e->keyReleaseFlag(mouse)) {
			if (mouseWidget) {
				mouseWidget->mouseEvent(MyMouseEvent(Release, mouse, e->mouseX - mouseWidget->wndX, e->mouseY - mouseWidget->wndY));
				e->setKeyReleaseFlag(mouse, false);
			}
		}
		if (mouseWidget) {
			e->setKeyFlag(mouse, false);
			e->setKeyPressFlag(mouse, false);
			e->setKeyReleaseFlag(mouse, false);
		}
	}

	//���
	if (mouseWidget) {
		mouseWidget->isMouseAt = false;
		mouseWidget = nullptr;
	}
	//���������ڿؼ�
	if (e->hasFocus) {
		for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
			MyWidget* w = *it;
			if (!w->isVisible())
				continue;
			int localX = e->mouseX - w->realX;
			int localY = e->mouseY - w->realY;
			if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
				w->mouseCheckAtEvent(localX, localY, &mouseWidget);
				break;
			}
		}
	}

	//�����л�
	if (changeRoomStr != "")
		return;
	//�̳����е��߼�����
	_onLogic();
}
void MyRoom::onRender() {
	_onRender();
	//���ƿؼ�
	for (auto it = widgets.begin(); it < widgets.end(); it++) {
		MyWidget* w = *it;
		if(w->isVisible())
			w->onRender(e->g_pSprite);
	}
}
void MyRoom::onDebug() {
	_onDebug();
}

void MyRoom::onResize() {
	_onResize();
}

void MyRoom::onDestroy() {
	_onDestroy();
	//���ٿؼ�
	for (auto it = widgets.begin(); it < widgets.end(); it++) {
		MyWidget* w = *it;
		w->onDestroy();
		safeDelete(w);
	}
	widgets.clear();
}