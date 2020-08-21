#pragma once

#include "../../Engine/Engine.h"

namespace My {
	class ListWidgetItem;
}

class My::ListWidgetItem
{
public:
	virtual ~ListWidgetItem() = default;

	enum class ItemFlag { None, MouseAt, MouseHolding, Focused };

	virtual void onPaint(RECT rect, ItemFlag flag, bool isFocused) {
		D3DCOLOR dwColor = 0;
		switch (flag) {
		case ItemFlag::None: dwColor = D3DCOLOR_XRGB(96, 192, 96); break;
		case ItemFlag::MouseAt: dwColor = D3DCOLOR_XRGB(96, 96, 192); break;
		case ItemFlag::MouseHolding: dwColor = D3DCOLOR_XRGB(192, 96, 96); break;
		}

		engine.drawRect(rect, dwColor);
		if (isFocused) {
			rect.left += 8;
			rect.top += 8;
			rect.right -= 8;
			rect.bottom -= 8;
			engine.drawRect(rect, D3DCOLOR_XRGB(192, 192, 96));
		}
	}
};