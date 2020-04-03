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

bool MyPushButton::mouseEvent(int type, int mouse, int x, int y) {
	cDebug("收到了鼠标事件~\n");
	if (type == MouseFlags::Press && signalPress) {
		signalPress(mouse);
	}
	else if (type == MouseFlags::Release && signalRelease) {
		signalRelease(mouse);
	}
	return true;
}

void MyPushButton::_onRender(LPD3DXSPRITE g_pSprite, int a, int r, int g, int b) {
	if(g_pFont)
		g_pFont->DrawText(e->g_pSprite, text.c_str(), -1, &rect(wndX, wndY, w, h), DT_CENTER | DT_VCENTER, textColor);
}

