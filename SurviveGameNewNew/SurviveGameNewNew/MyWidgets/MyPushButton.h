#ifndef _MYPUSHBUTTON_H
#define _MYPUSHBUTTON_H

#include "MyWidget.h"

class MyPushButton : public MyWidget
{
public:
	explicit MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, LPD3DXFONT g_pFont, 
		void (*signalPress)(int) = nullptr, void (*signalRelease)(int) = nullptr, MyWidget* parent = nullptr);
	~MyPushButton() override;

	bool mouseEvent(int type, int mouse, int x, int y) override;

	void _onRender(LPD3DXSPRITE g_pSprite) override;

	LPD3DXFONT g_pFont = nullptr;
	D3DCOLOR textColor1 = D3DCOLOR_XRGB(255, 255, 255), textColor2 = D3DCOLOR_XRGB(255, 255, 0);
	std::wstring text = TEXT("");
	

	void (*signalPress)(int) = nullptr, (*signalRelease)(int) = nullptr;
};

#endif //_MYPUSHBUTTON_H

