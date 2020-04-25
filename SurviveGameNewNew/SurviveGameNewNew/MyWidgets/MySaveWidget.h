#ifndef _MYSAVEWIDGET_H
#define _MYSAVEWIDGET_H

#include "MyWidget.h"
#include "../MyGame/MySave.h"

class MySaveWidget : public MyWidget
{
public:
	explicit MySaveWidget(MyEngine* e, int w, int h, MySave* save, LPD3DXFONT g_pFont, LPD3DXFONT g_pFontSmall, MyWidget* parent = nullptr);

	inline void _onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) override;

	MySave* save = nullptr;

	LPD3DXFONT g_pFont = nullptr, g_pFontSmall = nullptr;
	D3DCOLOR color = 0xffffffff;
	D3DCOLOR textColor = 0xff000000;
};

#endif