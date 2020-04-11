#include "MyRoom.h"

using namespace std;

MyRoom::MyRoom(MyEngine* e) {
	this->e = e;
}
MyRoom::~MyRoom(){}

void MyRoom::onBeforeKeyCheck() {
	if (focusWidget) {
		for (auto it = e->vec_keyBuffer.begin(); it < e->vec_keyBuffer.end(); it++) {
			MyKey* key = *it;
			if (key->flag) {	//按下按键
				focusWidget->keyboardEvent(key->key);
			}
		}
	}
}

void MyRoom::onLogic() {
	//响应输入字符
	wstring wstr = e->inputWString;
	e->inputWString = TEXT("");
	if (focusWidget && wstr != TEXT("")) {
		focusWidget->charEvent(wstr);
	}
	//控件事件
	int mouseArray[3]{VK_LBUTTON, VK_MBUTTON, VK_RBUTTON};
	for (int i = 0; i < 3; i++) {
		int mouse = mouseArray[i];
		if (e->keyPressFlag(mouse)) {
			bool flag = false;
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				if (!w->isVisible())
					continue;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MyMouseEvent(MouseFlags::Press, mouse, localX, localY, &focusWidget));
					e->setKeyPressFlag(mouse, false);
					if (mouse == VK_LBUTTON)
						flag = true;
					break;
				}
			}
			if (!flag)
				focusWidget = nullptr;
		}
		if (e->keyReleaseFlag(mouse)) {
			bool flag = false;
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				if (!w->isVisible())
					continue;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MyMouseEvent(MouseFlags::Release, mouse, localX, localY, &focusWidget));
					e->setKeyReleaseFlag(mouse, false);
					if (mouse == VK_LBUTTON)
						flag = true;
					break;
				}
			}
			if (!flag)
				focusWidget = nullptr;
		}
	}
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