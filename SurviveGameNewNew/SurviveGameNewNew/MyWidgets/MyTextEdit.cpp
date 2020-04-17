#include "MyTextEdit.h"

using namespace std;

MyTextEdit::MyTextEdit(MyEngine* e, int w, int h, LPD3DXFONT g_pFont, MyWidget** focusWidget, MyWidget* parent)
	: MyWidget(e, w, h, focusWidget, parent)
{
	this->g_pFont = g_pFont;
}

inline void MyTextEdit::resetFocusTimer() {
	focusTimer = 0;
	focusVisible = true;
}
void MyTextEdit::clear() {
	text = TEXT("");
	index = 0;
}

inline void MyTextEdit::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) {
	//绘制
	e->drawRestart();
	e->drawBorder(renderX, renderY, w, h, 1, bdColor, bdColor, bdColor, bdColor);
	e->drawRect(renderX + 1, renderY + 1, w - 2, h - 2, bgColor, bgColor, bgColor, bgColor);

	//绘制文字
	RECT textRect = rect(renderX + 1, renderY + 1, w - 2, h - 2);
	wstring tempStr = text;
	WCHAR& endChar = *tempStr.rbegin();
	if (endChar == TEXT(' '))
		endChar = TEXT('_');
	g_pFont->DrawText(g_pSprite, tempStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER, textColor);
	g_pFont->DrawText(g_pSprite, tempStr.c_str(), -1, &textRect,
		DT_CENTER | DT_VCENTER | DT_CALCRECT, textColor);

	//和光标相关的某个东西
	focusTimer++;
	if (focusTimer % 30 == 0) {
		focusVisible = !focusVisible;
		focusTimer = 0;
	}
	//绘制光标
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
			DT_CENTER | DT_VCENTER | DT_CALCRECT, textColor);
		int textOffset = textRect.right - textRect.left;

		//得到字符高度
		TEXTMETRIC met;
		g_pFont->GetTextMetrics(&met);
		int textHeight = met.tmHeight;

		//得到光标的位置
		int pos = textLeft + textOffset;
		//绘制
		if (pos > 0 && pos + 2 < w) {
			e->drawRestart();
			e->drawRect(renderX + pos - 1, renderY + (h - textHeight) / 2, 1, textHeight, textColor, textColor, textColor, textColor);
		}
	}
}

inline void MyTextEdit::_mouseEvent(MyMouseEvent) {
	resetFocusTimer();
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
		if (!expr.isNull)
			if (!expr.checkAccept(ch))
				continue;
		result += ch;
	}
	text.insert(index, result.c_str());
	index += result.length();

	resetFocusTimer();
}

inline void MyTextEdit::_keyboardEvent(int key) {
	switch (key) {
	case VK_LEFT:
		index--;
		resetFocusTimer();
		index = myBound<int>(0, index, text.length());
		break;
	case VK_RIGHT:
		index++;
		resetFocusTimer();
		index = myBound<int>(0, index, text.length());
		break;
	case VK_DELETE:
		if (index < (int)text.length())
			text.erase(index, 1);
		resetFocusTimer();
		break;
	}
}
