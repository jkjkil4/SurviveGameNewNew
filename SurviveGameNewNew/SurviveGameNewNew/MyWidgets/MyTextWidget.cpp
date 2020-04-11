#include "MyTextWidget.h"

MyTextWidget::MyTextWidget(MyEngine* e, int w, int h, LPD3DXFONT g_pFont, std::wstring text, MyWidget** focusWidget, MyWidget* parent)
	: MyWidget(e, w, h, focusWidget, parent)
{
	this->g_pFont = g_pFont;
	this->text = text;
}

inline void MyTextWidget::_onRender(LPD3DXSPRITE g_pSprite) {
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(wndX, wndY, w, h), format, textColor);
}

