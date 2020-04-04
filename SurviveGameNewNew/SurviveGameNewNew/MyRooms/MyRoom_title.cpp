#include "MyRoom_title.h"

using namespace std;

MyRoom_title* slotWidget = nullptr;

void btnSiglePressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSiglePressed(mouse);
}
void btnMultiPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnMultiPressed(mouse);
}
void btnSettingsPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnSettingsPressed(mouse);
}
void btnExitPressed(int mouse) {
	if (slotWidget)
		slotWidget->_btnExitPressed(mouse);
}

MyRoom_title::MyRoom_title(MyEngine* e) : MyRoom(e) {
	slotWidget = this;
	this->e = e;
	//窗口控件
	MyTexture* textureBtnBig = &e->data.guiTexture.btnBig;
	int offY = 40;

	MyPushButton* btnSigle = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSiglePressed);
	btnSigle->move(0, -70 + offY);
	btnSigle->text = stringToWstring("单人游戏(没做)");
	widgets.push_back(btnSigle);

	MyPushButton* btnMulti = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnMultiPressed);
	btnMulti->move(0, offY);
	btnMulti->text = stringToWstring("多人游戏(没做)");
	widgets.push_back(btnMulti);
	
	MyPushButton* btnSettings = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnSettingsPressed);
	btnSettings->move(0, 70 + offY);
	btnSettings->text = stringToWstring("设置(没做)");
	widgets.push_back(btnSettings);

	MyPushButton* btnExit = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont, btnExitPressed);
	btnExit->move(0, 140 + offY);
	btnExit->text = stringToWstring("退出");
	widgets.push_back(btnExit);
}
MyRoom_title::~MyRoom_title() {}

void MyRoom_title::_onLogic() {
	
}
void MyRoom_title::_onRender() {

}
void MyRoom_title::_onDebug() {

}

void MyRoom_title::_onDestroy() {

}

void MyRoom_title::_btnSiglePressed(int mouse) {

}
void MyRoom_title::_btnMultiPressed(int mouse) {

}
void MyRoom_title::_btnSettingsPressed(int mouse) {

}
void MyRoom_title::_btnExitPressed(int mouse) {
	SendMessage(e->g_hWnd, WM_CLOSE, 0, 0);
}