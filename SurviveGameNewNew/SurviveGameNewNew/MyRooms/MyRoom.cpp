#include "MyRoom.h"

MyRoom::MyRoom(MyEngine* e) {
	this->e = e;
}
MyRoom::~MyRoom(){}

void MyRoom::onLogic() {
	_onLogic();
	//控件事件
	int mouse[3]{VK_LBUTTON, VK_MBUTTON, VK_RBUTTON};
	//bool flag = false;
	for (int i = 0; i < 3; i++) {
		if (e->keyPressFlag(mouse[i])) {
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MouseFlags::Press, mouse[i], localX, localY);
					break;
				}
			}
		}
		if (e->keyReleaseFlag(mouse[i])) {
			for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
				MyWidget* w = *it;
				int localX = e->mouseX - w->realX;
				int localY = e->mouseY - w->realY;
				if (localX >= 0 && localX <= w->w && localY >= 0 && localY <= w->h) {
					w->mouseEvent(MouseFlags::Release, mouse[i], localX, localY);
					break;
				}
			}
		}
	}
	//if (flag) {
	//	for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {
	//		MyWidget* w = *it;

	//	}
	//}
}
void MyRoom::onRender() {
	_onRender();
	//绘制控件
	for (auto it = widgets.begin(); it < widgets.end(); it++)
		(*it)->onRender(e->g_pSprite);
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