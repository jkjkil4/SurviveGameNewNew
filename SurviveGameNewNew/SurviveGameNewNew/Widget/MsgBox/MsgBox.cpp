#include "MsgBox.h"

using namespace My;
using namespace std;

MsgBox::MsgBox(const std::wstring& title, LPFont titleFont, const std::wstring& text, LPFont textFont,
	const list<wstring>& lButtons, Image* btnImg, LPFont btnFont,
	int w, int h, Align align, Widget* parent)
	: Widget(w, h, align, parent), text(text), textFont(textFont), btnImg(btnImg)
{
	titleWidget = new TextLabel(title, titleFont, DT_CENTER | DT_VCENTER, w, titleHeight, Align::Top | Align::Left, this);
	titleWidget->move(0, 0);
	titleWidget->textColor = 0xffcccccc;

	int lBtnSize = lButtons.size();
	if (lBtnSize != 0) {
		if (lBtnSize == 1) {
			Button* btn = new Button(btnImg, *lButtons.begin(), btnFont, DT_CENTER | DT_VCENTER, Align::Bottom, this);
			btn->setSlot(this, (ButtonSlot)&MsgBox::onBtnClicked);
			btn->move(0, 5);
			vButtons.push_back(btn);
		}
		else {
			int start = 5;
			int end = w - 5 - btnImg->width;
			int count = 0;

			for (const wstring& btnText : lButtons) {
				Button* btn = new Button(btnImg, btnText, btnFont, DT_CENTER | DT_VCENTER, Align::Left | Align::Bottom, this);
				btn->setSlot(this, (ButtonSlot)&MsgBox::onBtnClicked);
				btn->move(start + (end - start) * count / (lBtnSize - 1), 5);
				vButtons.push_back(btn);
				count++;
			}
		}
	}
}


void MsgBox::onSelfRender(int renderX, int renderY) {
	engine.drawRect(renderX, renderY, w, titleHeight, titleBgColor);
	engine.drawRect(renderX, renderY + titleHeight, w, h - titleHeight, mainBgColor);

	RECT rect;
	rect.left = renderX + 5;
	rect.right = renderX + w - 5;
	rect.top = renderY + titleHeight + 5;
	rect.bottom = renderY + h - 5 - btnImg->height;
	textFont->DrawText(engine.g_pSprite, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER, mainTextColor);
}


void MsgBox::onBtnClicked(AbstractButton* btn) {
	if (slotObj) {
		int index = -1;
		int size = vButtons.size();
		for (int i = 0; i < size; i++) {
			if (vButtons[i] == btn) {
				index = i;
				break;
			}
		}
		(slotObj->*slot)(index);
	}
}


void MsgBox::setSlot(Object* _slotObj, MsgBoxSlot _slot) {
	slotObj = _slotObj;
	slot = _slot;
}