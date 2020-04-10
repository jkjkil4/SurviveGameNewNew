#include "MyTextEdit.h"

using namespace std;

MyTextEdit::MyTextEdit(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo,
	LPD3DXFONT g_pFont, MyWidget** focusWidget, MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, focusWidget, parent)
{
	this->g_pFont = g_pFont;
}

inline void MyTextEdit::resetFocus() {
	focusTimer = 0;
	focusVisible = true;
}

inline void MyTextEdit::_onRender(LPD3DXSPRITE g_pSprite) {
	RECT textRect = rect(wndX, wndY, w, h);
	wstring tempStr = text;
	WCHAR& endChar = *tempStr.rbegin();
	if (endChar == TEXT(' '))
		endChar = TEXT('_');
	g_pFont->DrawText(g_pSprite, tempStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER, 0xffffffff);
	g_pFont->DrawText(g_pSprite, tempStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER | DT_CALCRECT, 0xffffffff);

	focusTimer++;
	if (focusTimer % 30 == 0) {
		focusVisible = !focusVisible;
		focusTimer = 0;
	}
	if (this == *focusWidget && focusVisible) {
		//得到字符串宽度
		int textWidth = textRect.right - textRect.left;
		//得到字符串左侧的位置
		int textLeft = (w - textWidth) / 2;

		//得到光标偏移
		if (index > 0) {
			WCHAR& ch = *(tempStr.begin() + (index - 1));
			if (ch == TEXT(' '))
				ch = TEXT('_');
		}
		g_pFont->DrawText(g_pSprite, tempStr.c_str(), index, &textRect, 
			DT_CENTER | DT_VCENTER | DT_CALCRECT, 0xffffffff);
		int textOffset = textRect.right - textRect.left;

		//得到字符高度
		TEXTMETRIC met;
		g_pFont->GetTextMetrics(&met);
		int textHeight = met.tmHeight;

		//得到光标的位置
		int pos = textLeft + textOffset;
		//绘制
		if (pos > 0 && pos + 2 < w)
			e->drawRect(wndX + pos - 1, wndY + (h - textHeight) / 2, 2, textHeight);
	}
}

inline void MyTextEdit::_mouseEvent(MyMouseEvent) {
	resetFocus();
}

inline void MyTextEdit::_charEvent(wstring wstr) {
	wstring result = TEXT("");
	for (int i = 0; i < (int)wstr.length(); i++) {
		WCHAR ch = wstr[i];
		if (ch < 0x0020) {	//除去控制字符
			if (ch == 0x0008) {	//退格键
				if (i == 0) {
					if (text.length() != 0 && index > 0) {
						index--;
						text.erase(index, 1);
					}
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
		if (maxLength != -1)
			if ((int)(text.length() + result.length()) >= maxLength)
				continue;
		result += ch;
	}
	text.insert(index, result.c_str());
	index += result.length();

	resetFocus();
}

inline void MyTextEdit::_keyboardEvent(int key) {
	switch (key) {
	case VK_LEFT:
		index--;
		resetFocus();
		index = myBound<int>(0, index, text.length());
		break;
	case VK_RIGHT:
		index++;
		resetFocus();
		index = myBound<int>(0, index, text.length());
		break;
	case VK_DELETE:
		if (index < (int)text.length())
			text.erase(index, 1);
		break;
	}
}
