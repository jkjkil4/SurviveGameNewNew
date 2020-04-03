#include "MyRoom.h"

MyRoom::MyRoom(MyEngine* e) {
	this->e = e;
}
MyRoom::~MyRoom(){}

void MyRoom::onLogic() {
	_onLogic();
}
void MyRoom::onRender() {
	_onRender();
	//���ƿؼ�
	for (auto it = widgets.begin(); it < widgets.end(); it++)
		(*it)->onRender(e->g_pSprite, 255, 255, 255);
}
void MyRoom::onDebug() {
	_onDebug();
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