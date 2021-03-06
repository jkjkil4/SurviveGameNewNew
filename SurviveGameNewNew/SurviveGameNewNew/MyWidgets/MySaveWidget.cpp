#include "MySaveWidget.h"

MySaveWidget::MySaveWidget(MyEngine* e, int w, int h, MySave* save, LPD3DXFONT g_pFont, LPD3DXFONT g_pFontSmall, MyWidget* parent)
	: MyWidget(e, w, h, nullptr, parent),
	save(save), g_pFont(g_pFont), g_pFontSmall(g_pFontSmall) {}

inline void MySaveWidget::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	//���Ʊ���
	D3DCOLOR bgColor = color;
	if (shownSave) {
		if (save == *shownSave)
			bgColor = selColor;
	}
	e->drawRect(renderX, renderY, w, h, bgColor, bgColor, bgColor, bgColor);

	//��������
	if (save->info) {
		MySave::Info* info = save->info;
		RECT allowedRect = rect(renderX + 3, renderY + 3, w - 6, h - 8);
		g_pFont->DrawText(g_pSprite, info->name.c_str(), -1, &allowedRect, DT_LEFT | DT_TOP, textColor);
		g_pFontSmall->DrawText(g_pSprite, info->fileName.c_str(), -1, &allowedRect, DT_LEFT | DT_BOTTOM, textColor2);

	}
}

inline void MySaveWidget::_mouseEvent(MyMouseEvent ev) {
	if (ev.type == Press && ev.mouse == VK_LBUTTON)
		if (shownSave)
			*shownSave = save;
}

