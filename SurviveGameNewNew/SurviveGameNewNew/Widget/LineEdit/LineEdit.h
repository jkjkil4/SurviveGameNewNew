#pragma once

#include "../AbstractLineEdit/AbstractLineEdit.h"

namespace My {
	class LineEdit;
}

class My::LineEdit : public AbstractLineEdit
{
public:
	LineEdit(LPFont font, TextAlign textAlign, int w, int h, Align align = Align::None, Widget* parent = nullptr);
	~LineEdit() override = default;

	void onSelfRender(int renderX, int renderY) override;

	D3DCOLOR borderColor = 0xffffffff;	//±ß¿òÑÕÉ«
	D3DCOLOR backgroundColor = 0xff000000;	//±³¾°ÑÕÉ«
};