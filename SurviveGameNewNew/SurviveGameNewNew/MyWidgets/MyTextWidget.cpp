#include "MyTextWidget.h"

MyTextWidget::MyTextWidget(MyEngine* e, int w, int h, LPD3DXFONT g_pFont, std::wstring text, MyWidget** focusWidget, MyWidget* parent)
	: MyWidget(e, w, h, focusWidget, parent),
	g_pFont(g_pFont), text(text) {}

inline void MyTextWidget::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(renderX, renderY, w, h), format, textColor);
}

