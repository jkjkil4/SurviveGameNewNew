#include "MyPushButton.h"

using namespace std;

MyPushButton::MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, nullptr, parent), 
	g_pFont(g_pFont) {}


void MyPushButton::setPressSlot(void(MyRoom::* pressSlotFunc)(MyMouseEvent), MyRoom* pressSlot) {
	this->pressSlotFunc = (void(MyRoom::*)(MyMouseEvent))pressSlotFunc;
	this->pressSlot = pressSlot;
}

void MyPushButton::setReleaseSlot(void(MyRoom::* releaseSlotFunc)(MyMouseEvent), MyRoom* releaseSlot) {
	this->releaseSlotFunc = (void(MyRoom::*)(MyMouseEvent))releaseSlotFunc;
	this->releaseSlot = releaseSlot;
}

inline void MyPushButton::_mouseEvent(MyMouseEvent ev) {
	if (ev.type == MouseFlags::Press && pressSlot && pressSlotFunc) {
		(pressSlot->*pressSlotFunc)(ev);
	}
	else if (ev.type == MouseFlags::Release && releaseSlot && releaseSlotFunc) {
		(releaseSlot->*releaseSlotFunc)(ev);
	}
}

inline void MyPushButton::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(renderX, renderY, w, h), DT_CENTER | DT_VCENTER, 
		isMouseAt ? textColor2 : textColor1);
}