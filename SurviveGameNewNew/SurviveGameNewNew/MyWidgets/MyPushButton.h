#ifndef _MYPUSHBUTTON_H
#define _MYPUSHBUTTON_H

#include "MyWidget.h"

class MyPushButton : public MyWidget
{
public:
	explicit MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, 
		void (*signalPress)(MyMouseEvent ev) = nullptr, void (*signalRelease)(MyMouseEvent ev) = nullptr, MyWidget* parent = nullptr);
	~MyPushButton() override;

	inline void _mouseEvent(MyMouseEvent ev) override;

	inline void _onRender(LPD3DXSPRITE g_pSprite) override;

	LPD3DXFONT g_pFont = nullptr;
	D3DCOLOR textColor1 = D3DCOLOR_XRGB(255, 255, 255), textColor2 = D3DCOLOR_XRGB(255, 255, 0);
	std::wstring text = TEXT("");
	

	void (*signalPress)(MyMouseEvent ev) = nullptr, (*signalRelease)(MyMouseEvent ev) = nullptr;
};

#endif //_MYPUSHBUTTON_H

