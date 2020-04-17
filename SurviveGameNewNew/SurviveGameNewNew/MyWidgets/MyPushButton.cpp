#include "MyPushButton.h"

using namespace std;

MyPushButton::MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, 
	void (*signalPress)(MyMouseEvent ev), void (*signalRelease)(MyMouseEvent ev), MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, nullptr, parent) 
{
	this->g_pFont = g_pFont;
	this->signalPress = signalPress;
	this->signalRelease = signalRelease;
}

MyPushButton::~MyPushButton(){}

inline void MyPushButton::_mouseEvent(MyMouseEvent ev) {
	if (ev.type == MouseFlags::Press && signalPress) {
		signalPress(ev);
	}
	else if (ev.type == MouseFlags::Release && signalRelease) {
		signalRelease(ev);
	}
}

inline void MyPushButton::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(renderX, renderY, w, h), DT_CENTER | DT_VCENTER, 
		isMouseAt ? textColor2 : textColor1);
}