#pragma once

#include "../Widget.h"

#include "../../Class/Image.h"

namespace My {
	class ImageLabel;
}

class My::ImageLabel : public Widget
{
public:
	ImageLabel(Image* img, Align align = Align::None, Widget* parent = nullptr)
		: Widget(img->width, img->height, align, parent), g_pTexture(img->g_pTexture) {}
	~ImageLabel() override = default;

	LPTexture g_pTexture;
	D3DCOLOR mixColor = 0xffffffff;

	void onSelfRender(int renderX, int renderY) override;
};

