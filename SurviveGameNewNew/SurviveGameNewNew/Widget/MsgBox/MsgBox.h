#pragma once

#include "../Widget.h"

#include "../TextLabel/TextLabel.h"
#include "../Button/Button.h"

namespace My {
	class MsgBox;
	typedef void(Object::* MsgBoxSlot)(int);
}

class My::MsgBox : public Widget
{
public:
	MsgBox(const std::wstring& title, LPFont titleFont, const std::wstring& text, LPFont textFont,
		const std::list<std::wstring>& lButtons, Image* btnImg, LPFont btnFont,
		int w, int h, Align align = Align::None, Widget* parent = nullptr);

	void onSelfRender(int renderX, int renderY);

	void onBtnClicked(AbstractButton* btn);

	void setSlot(Object* _slotObj, MsgBoxSlot _slot);
	Object* slotObj = nullptr;
	MsgBoxSlot slot = nullptr;

	static constexpr int titleHeight = 20;

	TextLabel* titleWidget;

	std::wstring text;
	LPFont textFont;
	Image* btnImg;

	D3DCOLOR titleBgColor = D3DCOLOR_XRGB(82, 82, 148);
	//D3DCOLOR titleTextColor = 0xffcccccc;
	D3DCOLOR mainBgColor= D3DCOLOR_XRGB(60, 60, 115);
	D3DCOLOR mainTextColor = 0xffffffff;

	std::vector<Button*> vButtons;
};