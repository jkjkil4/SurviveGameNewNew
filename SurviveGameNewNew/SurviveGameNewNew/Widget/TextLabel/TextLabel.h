#pragma once

#include "../Widget.h"

namespace My {
	class TextLabel;
}

class My::TextLabel : public Widget
{
public:
	TextLabel(std::wstring text, LPFont font, DWORD textAlign, int w, int h, Align align = Align::None, Widget* parent = nullptr)
		: Widget(w, h, align, parent), text(text), font(font), textAlign(textAlign) {}
	~TextLabel() override = default;

	void onSelfRender(int renderX, int renderY) override;

	std::wstring text;
	LPFont font;
	DWORD textAlign;

	D3DCOLOR textColor = 0xffffffff;
};