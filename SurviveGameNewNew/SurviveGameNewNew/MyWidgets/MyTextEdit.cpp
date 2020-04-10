#include "MyTextEdit.h"

using namespace std;

MyTextEdit::MyTextEdit(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo,
	LPD3DXFONT g_pFont, MyWidget** focusWidget, MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, focusWidget, parent)
{
	this->g_pFont = g_pFont;
}

inline void MyTextEdit::_onRender(LPD3DXSPRITE g_pSprite) {
	RECT textRect = rect(wndX, wndY, w, h);
	wstring fixedStr = text;
	WCHAR& endChar = *fixedStr.rbegin();
	if (endChar == TEXT(' '))
		endChar = TEXT('_');
	g_pFont->DrawText(g_pSprite, fixedStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER, 0xffffffff);
	g_pFont->DrawText(g_pSprite, fixedStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER | DT_CALCRECT, 0xffffffff);

	focusTimer++;
	if (focusTimer % 30 == 0) {
		focusVisible = !focusVisible;
		focusTimer = 0;
	}
	if (this == *focusWidget && focusVisible) {
		TEXTMETRIC met;
		g_pFont->GetTextMetrics(&met);
		int charWidth = textRect.right - textRect.left;
		int charHeight = 20;
		int bor = h - charHeight;
		int textRight = (w + charWidth) / 2;
		if (textRight + 2 < w)
			e->drawRect(wndX + textRight, wndY + bor / 2, 2, charHeight);
	}
}

inline void MyTextEdit::_mouseEvent(MyMouseEvent) {
	focusTimer = 0;
	focusVisible = true;
}

inline void MyTextEdit::_keyboardEvent(wstring wstr) {
	wstring result = TEXT("");
	for (int i = 0; i < (int)wstr.length(); i++) {
		WCHAR ch = wstr[i];
		if (ch < 0x0020) {	//³ýÈ¥¿ØÖÆ×Ö·û
			if (ch == 0x0008) {	//ÍË¸ñ¼ü
				if (i == 0) {
					if (text.length() != 0)
						text.pop_back();
				}
				else {
					if (result.length() != 0)
						result.pop_back();
				}
				focusTimer = 0;
				focusVisible = true;
			}
			continue;
		}
		result += ch;
	}
	text += result;
	focusTimer = 0;
	focusVisible = true;
}
