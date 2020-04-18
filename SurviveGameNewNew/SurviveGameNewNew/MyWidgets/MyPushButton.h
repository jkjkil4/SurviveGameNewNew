#ifndef _MYPUSHBUTTON_H
#define _MYPUSHBUTTON_H

#include "MyWidget.h"

#include "../MyRooms/MyRoom.h"

#define PUSH_BUTTON_SLOT(func) ((void(MyRoom::*)(MyMouseEvent))func) 

class MyPushButton : public MyWidget
{
public:
	explicit MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, MyWidget* parent = nullptr);
	~MyPushButton() override;

	void setPressSlot(void(MyRoom::* pressSignal)(MyMouseEvent), MyRoom* pressSlot);

	void setReleaseSlot(void(MyRoom::* releaseSignal)(MyMouseEvent), MyRoom* releaseSlot);

	inline void _mouseEvent(MyMouseEvent ev) override;

	inline void _onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) override;

	LPD3DXFONT g_pFont = nullptr;
	D3DCOLOR textColor1 = D3DCOLOR_XRGB(255, 255, 255), textColor2 = D3DCOLOR_XRGB(255, 255, 0);
	std::wstring text = TEXT("");
	

	void (MyRoom::* pressSlotFunc)(MyMouseEvent ev) = nullptr;
	MyRoom* pressSlot = nullptr;

	void (MyRoom::* releaseSlotFunc)(MyMouseEvent ev) = nullptr;
	MyRoom* releaseSlot = nullptr;
};

#endif //_MYPUSHBUTTON_H

