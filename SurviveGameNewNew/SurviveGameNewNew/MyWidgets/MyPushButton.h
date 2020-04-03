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

	void _onRender(LPD3DXSPRITE g_pSprite, int a, int r, int g, int b) override;

	LPD3DXFONT g_pFont = nullptr;
	D3DXCOLOR textColor = D3DCOLOR_XRGB(0, 0, 0);
	std::wstring text = TEXT("");

	void (*signalPress)(int) = nullptr, (*signalRelease)(int) = nullptr;
};

#endif //_MYPUSHBUTTON_H

