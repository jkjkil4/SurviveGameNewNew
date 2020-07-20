#pragma once

#include "../AbstractButton/AbstractButton.h"

namespace My {
	class Button;
}

class My::Button : public AbstractButton
{
public:
	Button(Image* img, std::wstring text, LPFont font, DWORD textAlign, Align align = Align::None, Widget* parent = nullptr) 
		: AbstractButton(img->width, img->height, align, parent), 
		g_pTexture(img->g_pTexture), font(font), text(text), textAlign(textAlign) {}
	~Button() override = default;

	void onSelfRender(int renderX, int renderY) override;

	LPTexture g_pTexture;

	std::wstring text;
	LPFont font;
	DWORD textAlign;

	D3DCOLOR mixColor = 0xffffffff;
	D3DCOLOR textColor = 0xffffffff;
};