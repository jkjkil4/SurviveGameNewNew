#include "MySaveWidget.h"

MySaveWidget::MySaveWidget(MyEngine* e, int w, int h, MySave* save, LPD3DXFONT g_pFont, LPD3DXFONT g_pFontSmall, MyWidget* parent)
	: MyWidget(e, w, h, nullptr, parent)
{
	this->save = save;
	this->g_pFont = g_pFont;
	this->g_pFontSmall = g_pFontSmall;
}

inline void MySaveWidget::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	e->drawRect(renderX, renderY, w, h, color, color, color, color);
	if (save->info) {
		MySave::Info* info = save->info;
		RECT allowedRect = rect(renderX + 3, renderY + 3, w - 6, h - 6);
		g_pFont->DrawText(g_pSprite, info->name.c_str(), -1, &allowedRect, DT_LEFT | DT_TOP, textColor);
	}
}

