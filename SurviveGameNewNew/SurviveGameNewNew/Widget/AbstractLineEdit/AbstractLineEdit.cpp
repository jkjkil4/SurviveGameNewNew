#include "AbstractLineEdit.h"

using namespace My;
using namespace std;

//得到单个字符的宽度
#define GET_WCHAR_WIDTH(resultVaribleName, wchar) {\
	RECT wchRect;\
	WCHAR wch = wchar;\
	if (wch == _T(' ')) wch = _T('_');\
	font->DrawText(engine.g_pSprite, &wch, 1, &wchRect, DT_CALCRECT, 0);\
	resultVaribleName = rectWidth(wchRect);\
}


AbstractLineEdit::AbstractLineEdit(LPFont font, TextAlign textAlign, int w, int h, Align align, Widget* parent)
	: font(font), textAlign(textAlign), Widget(w, h, align, parent) 
{
	cursorShape = IDC_IBEAM;	//设置鼠标悬停样式为文本编辑
	createRenderTarget();	//使用RenderTarget
}


void AbstractLineEdit::onLogic() {
	//和光标闪烁有关的东西
	cursorShowCountTimes++;
	if (cursorShowCountTimes > cursorShowTimes) {
		cursorShowCountTimes = 0;
		isCursorShow = !isCursorShow;
	}

	Widget::onLogic();
}

void AbstractLineEdit::onMousePressed(MouseEvent* ev) {
	//光标位置
	cursorBegin = getCursorIndex(ev->mouseX);
	cursorEnd = cursorBegin;

	//将光标设置为可见状态
	setCursorEnable();
}

void AbstractLineEdit::onMouseMove(MouseEvent* ev) {
	//光标位置
	cursorEnd = getCursorIndex(ev->mouseX);
}

void AbstractLineEdit::onKeyPressed(KeyEvent* ev) {
	switch (ev->key) {
	case VK_BACK:	//退格键(删除文字)
		if (cursorBegin == cursorEnd) {
			if (cursorEnd > 0) {
				cursorBegin--;
				cursorEnd--;
				text.erase(text.begin() + cursorEnd);
			}
		}
		else {
			text.erase(text.begin() + min(cursorBegin, cursorEnd), text.begin() + max(cursorBegin, cursorEnd));

			int res = min(cursorBegin, cursorEnd);
			cursorBegin = res;
			cursorEnd = res;
		}
		setCursorEnable();
		break;
	case VK_LEFT:	//键盘向左键(光标左移)
		if (cursorBegin == cursorEnd) {
			if (cursorEnd > 0) {
				cursorBegin--;
				cursorEnd--;
			}
		}
		else {
			int res = min(cursorBegin, cursorEnd);
			cursorBegin = res;
			cursorEnd = res;
		}
		setCursorEnable();
		break;
	case VK_RIGHT:	//键盘向右键(光标右移)
		if (cursorBegin == cursorEnd) {
			if (cursorEnd < (int)text.length()) {
				cursorBegin++;
				cursorEnd++;
			}
		}
		else {
			int res = max(cursorBegin, cursorEnd);
			cursorBegin = res;
			cursorEnd = res;
		}
		setCursorEnable();
		break;
	}
}

void AbstractLineEdit::onTextInput(wstring& input) {
	wstring insertText;
	//insertText.resize(input.length());

	int res;
	for (auto iter = input.begin(); iter < input.end(); iter++) {
		WCHAR wch = *iter;
		if (wch < 0x0020) continue;	//除去控制字符
		insertText += wch;
	}
	if (insertText.length() == 0)
		return;
	if (cursorBegin == cursorEnd) {
		res = cursorEnd + insertText.length();
		text.insert(cursorEnd, insertText.c_str());
		
	}
	else {
		res = min(cursorBegin, cursorEnd) + insertText.length();
		text.erase(text.begin() + min(cursorBegin, cursorEnd), text.begin() + max(cursorBegin, cursorEnd));
		text.insert(min(cursorBegin, cursorEnd), insertText.c_str());
	}
	cursorBegin = res;
	cursorEnd = res;

	setCursorEnable();
}


void AbstractLineEdit::setCursorEnable() {
	cursorShowCountTimes = 0;
	isCursorShow = true;
}

void AbstractLineEdit::updateOffsetByIndex(int index) {

}

int AbstractLineEdit::getTextWidth() {
	if (text.length() == 0)
		return 0;
	RECT tmpRect;
	font->DrawText(engine.g_pSprite, _T("_"), 1, &tmpRect, DT_CALCRECT, 0);
	int perSpaceWidth = rectWidth(tmpRect);
	int spaceCount = 0;
	for (auto iter = text.rbegin(); iter < text.rend(); iter++) {
		if (*iter == ' ') {
			spaceCount++;
		}
		else break;
	}
	font->DrawText(engine.g_pSprite, text.c_str(), text.length() - spaceCount, &tmpRect, DT_CALCRECT, 0);
	return rectWidth(tmpRect) + perSpaceWidth * spaceCount;
}

int AbstractLineEdit::getIndexX(int index) {
	if (index < 0 || index >(int)text.length())
		return 0;

	switch (textAlign) {
	case TextAlign::Center: {
		if (text.length() == 0)
			return boxOffset.xOffset + (w + boxOffset.wOffset) / 2;
		if (index == 0)
			return boxOffset.xOffset + (w + boxOffset.wOffset - getTextWidth()) / 2;
		bool isReplacedSpace = false;
		if (text[index - 1] == _T(' ')) {
			text[index - 1] = _T('_');
			isReplacedSpace = true;
		}
		RECT tmpRect;
		font->DrawText(engine.g_pSprite, text.c_str(), index, &tmpRect, DT_CALCRECT, 0);
		int offsetWidth = rectWidth(tmpRect);
		if (isReplacedSpace)
			text[index - 1] = _T(' ');
		return boxOffset.xOffset + (w + boxOffset.wOffset - getTextWidth()) / 2 + offsetWidth;
	}
	case TextAlign::Left: {
		if (text.length() == 0 || index == 0)
			return margin;
		bool isReplacedSpace = false;
		if (text[index - 1] == _T(' ')) {
			text[index - 1] = _T('_');
			isReplacedSpace = true;
		}
		RECT tmpRect;
		font->DrawText(engine.g_pSprite, text.c_str(), index, &tmpRect, DT_CALCRECT, 0);
		int offsetWidth = rectWidth(tmpRect);
		if (isReplacedSpace)
			text[index - 1] = _T(' ');
		return margin + offsetWidth;
	}
	case TextAlign::Scroll: {
		if (text.length() == 0)
			return margin;
		if (index > strPos) {
			bool isReplacedSpace = false;
			if (text[index - 1] == _T(' ')) {
				text[index - 1] = _T('_');
				isReplacedSpace = true;
			}
			RECT tmpRect;
			font->DrawText(engine.g_pSprite, text.c_str() + strPos, index - strPos, &tmpRect, DT_CALCRECT, 0);
			int offsetWidth = rectWidth(tmpRect);
			if (isReplacedSpace)
				text[index - 1] = _T(' ');
			return margin - charOffset + offsetWidth;
		}
		else if (index < strPos) {
			bool isReplacedSpace = false;
			if (text[strPos - 1] == _T(' ')) {
				text[strPos - 1] = _T('_');
				isReplacedSpace = true;
			}
			RECT tmpRect;
			font->DrawText(engine.g_pSprite, text.c_str() + index, strPos - index, &tmpRect, DT_CALCRECT, 0);
			int offsetWidth = rectWidth(tmpRect);
			if (isReplacedSpace)
				text[strPos - 1] = _T(' ');
			return margin - charOffset - offsetWidth;
		}
		else {
			return margin - charOffset;
		}
	}
	}
	return 0;
}



int AbstractLineEdit::getCursorIndex(int mouseX) {
	switch (textAlign) {
	case TextAlign::Center:
	case TextAlign::Left: {
		int left = textAlign == TextAlign::Center ? boxOffset.xOffset + (w + boxOffset.wOffset - getTextWidth()) / 2 : margin;	//得到文本最左端的位置
		if (left > mouseX)	//如果文本最左端大于鼠标坐标
			return 0;	//返回0
		int strLen = text.length();
		int procIndex = 0;
		while (procIndex < strLen) {
			//得到字符宽度
			int wchWidth;
			GET_WCHAR_WIDTH(wchWidth, text[procIndex]);

			//一些操作
			left += wchWidth;
			if (left > mouseX)	//鼠标在文本中间
				return left - mouseX < wchWidth / 2 ? procIndex + 1 : procIndex;
			procIndex++;
		}
		//鼠标在文本结尾更往后的地方
		return strLen;
	}
	case TextAlign::Scroll:
		int start = -charOffset;
		int procIndex = strPos;
		if (mouseX < start) {	//如果鼠标在start左侧
			procIndex--;
			while (procIndex >= 0) {
				//得到字符宽度
				int wchWidth;
				GET_WCHAR_WIDTH(wchWidth, text[procIndex]);

				start -= wchWidth;
				if (start < mouseX)	//鼠标在文本起始和start之间
					return mouseX - start < wchWidth / 2 ? procIndex : procIndex + 1;
				procIndex--;
			}
			//鼠标在文本起始更往前的地方
			return 0;
		}
		else {	//否则
			int strLen = text.length();
			while (procIndex < strLen) {
				//得到字符宽度
				int wchWidth;
				GET_WCHAR_WIDTH(wchWidth, text[procIndex]);

				start += wchWidth;
				if (start > mouseX)	//鼠标在start和文本结尾之间
					return start - mouseX < wchWidth / 2 ? procIndex + 1 : procIndex;
				procIndex++;
			}
			//鼠标在文本结尾更往后的地方
			return strLen;
		}
	}
	return 0;
}

void AbstractLineEdit::drawText(int renderX, int renderY) {
	RECT rect = mkRect(renderX + boxOffset.xOffset, renderY + boxOffset.yOffset, w + boxOffset.wOffset, h + boxOffset.hOffset);
	//绘制文字
	switch(textAlign){
	case TextAlign::Center:
		//调整
		rect.left += (rectWidth(rect) - getTextWidth()) / 2;
		//绘制文字
		font->DrawText(engine.g_pSprite, text.c_str(), -1, &rect, DT_LEFT | DT_VCENTER | DT_NOCLIP, textColor);
		break;
	case TextAlign::Left:
		rect.left += margin;
		font->DrawText(engine.g_pSprite, text.c_str(), -1, &rect, DT_LEFT | DT_VCENTER | DT_NOCLIP, textColor);
		break;
	case TextAlign::Scroll:
		RECT textRect;
		textRect.top = rect.top;
		textRect.bottom = rect.bottom;

		int offsetX = margin - charOffset;
		int procIndex = strPos;
		int boxWidth = rectWidth(rect);
		int strLen = text.length();

		while (offsetX < boxWidth && procIndex < strLen) {
			//得到字符宽度
			int wchWidth;
			GET_WCHAR_WIDTH(wchWidth, text[procIndex]);

			//绘制字符
			textRect.left = rect.left + offsetX;
			textRect.right = textRect.left + wchWidth;
			font->DrawText(engine.g_pSprite, text.c_str() + procIndex, 1, &textRect, DT_VCENTER | DT_NOCLIP, textColor);

			procIndex++;
			offsetX += wchWidth;
		}
		break;
	}


	//绘制选择部分
	TEXTMETRIC textMetric;
	font->GetTextMetrics(&textMetric);

	if (isFocusWidget) {
		if (cursorBegin == cursorEnd) {
			if (isCursorShow) {
				int xPos = getIndexX(cursorBegin);
				RECT drawRect = mkRect(xPos, boxOffset.yOffset + (h + boxOffset.hOffset - textMetric.tmHeight) / 2 - 2, 2, textMetric.tmHeight + 4);
				
				engine.drawRestart();
				engine.setPixelShader(&pixelShaderMap[_T("ReverseColor")]);
				engine.g_pSprite->Draw(g_pTargetTexture, &drawRect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
					&D3DXVECTOR3((float)(renderX + drawRect.left), (float)(renderY + drawRect.top), 0.0f), 0xffffffff);
				engine.setPixelShader(nullptr);
			}
		}
		else {
			int beginX = getIndexX(cursorBegin);
			int endX = getIndexX(cursorEnd);
			int leftX = min(beginX, endX);
			int rightX = max(beginX, endX);
			RECT drawRect = mkRect(leftX, boxOffset.yOffset + (h + boxOffset.hOffset - textMetric.tmHeight) / 2 - 2, rightX - leftX, textMetric.tmHeight + 4);

			engine.drawRestart();
			engine.setPixelShader(&pixelShaderMap[_T("ReverseColor")]);
			engine.g_pSprite->Draw(g_pTargetTexture, &drawRect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				&D3DXVECTOR3((float)(renderX + drawRect.left), (float)(renderY + drawRect.top), 0.0f), 0xffffffff);
			engine.setPixelShader(nullptr);
		}
	}

#ifdef DEBUG_LINEEDIT
	//调试
	engine.g_pFontVerySmall->DrawText(engine.g_pSprite, (_T("cursorBegin: ") + std::to_wstring(cursorBegin) + _T("  cursorEnd: ") + std::to_wstring(cursorEnd)).c_str(),
		-1, &mkRect(renderX + boxOffset.xOffset, renderY + boxOffset.yOffset, w + boxOffset.wOffset, h + boxOffset.hOffset), DT_LEFT | DT_TOP | DT_NOCLIP, 0xffff0000);
#endif
}