#ifndef _MYTEXTWIDGET_H
#define _MYTEXTWIDGET_H

#include "MyWidget.h"

class MyTextWidget : public MyWidget
{
public:
	explicit MyTextWidget(MyEngine* e, int w, int h, LPD3DXFONT g_pFont, std::wstring text, MyWidget** focusWidget = nullptr, MyWidget* parent = nullptr);
	~MyTextWidget() override = default;

	inline void _onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) override;

	DWORD format = 0;
	D3DCOLOR textColor = D3DCOLOR_XRGB(0, 0, 0);

	LPD3DXFONT g_pFont = nullptr;
	std::wstring text = TEXT("");
};

#endif

