#include "MyPushButton.h"

using namespace std;

MyPushButton::MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, 
	void (*signalPress)(int), void (*signalRelease)(int), MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, parent) 
{
	this->g_pFont = g_pFont;
	this->signalPress = signalPress;
	this->signalRelease = signalRelease;
}

MyPushButton::~MyPushButton(){}

void MyPushButton::_mouseEvent(int type, int mouse, int x, int y) {
	if (type == MouseFlags::Press && signalPress) {
		signalPress(mouse);
	}
	else if (type == MouseFlags::Release && signalRelease) {
		signalRelease(mouse);
	}
}

void MyPushButton::_onRender(LPD3DXSPRITE g_pSprite) {
	int localX = e->mouseX - wndX, localY = e->mouseY - wndY;
	bool flag = (localX >= 0 && localY >= 0 && localX <= w && localY <= h);
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(wndX, wndY, w, h), DT_CENTER | DT_VCENTER, 
		flag ? textColor2 : textColor1);
}