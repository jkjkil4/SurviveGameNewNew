#include "MyRoom.h"

MyRoom::MyRoom(MyEngine* e) {
	this->e = e;
}
MyRoom::~MyRoom(){}

void MyRoom::onLogic() {
	//控件事件
	int mouseArray[3]{VK_LBUTTON, VK_MBUTTON, VK_RBUTTON};
	bool flag = false;
	for (int i = 0; i < 3; i++) {
		int mouse = mouseArray[i];
		if (e->keyPressFlag(mouse)) {
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				if (!w->isVisible())
					continue;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MouseFlags::Press, mouse, localX, localY);
					e->setKeyPressFlag(mouse, false);
					break;
				}
			}
		}
		if (e->keyReleaseFlag(mouse)) {
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				if (!w->isVisible())
					continue;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MouseFlags::Release, mouse, localX, localY);
					e->setKeyReleaseFlag(mouse, false);
					break;
				}
			}
		}
	}
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