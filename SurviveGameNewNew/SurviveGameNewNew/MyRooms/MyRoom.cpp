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
			if (key->flag) {	//按下按键
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
	//响应输入字符
	wstring wstr = e->inputWString;
	e->inputWString = TEXT("");
	if (focusWidget && wstr != TEXT("")) {
		focusWidget->charEvent(wstr);
	}
	
	//鼠标滚轮
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

	//控件事件
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

	//清除
	if (mouseWidget) {
		mouseWidget->isMouseAt = false;
		mouseWidget = nullptr;
	}
	//检测鼠标所在控件
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

	//房间切换
	if (changeRoomStr != "")
		return;
	//继承类中的逻辑处理
	_onLogic();
}
void MyRoom::onRender() {
	_onRender();
	//绘制控件
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
	//销毁控件
	for (auto it = widgets.begin(); it < widgets.end(); it++) {
		MyWidget* w = *it;
		w->onDestroy();
		safeDelete(w);
	}
	widgets.clear();
}