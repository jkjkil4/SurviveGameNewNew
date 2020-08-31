#pragma once

#include "../../../Game/Save.h"
#include "../ListWidgetItem.h"

namespace My {
	class SaveListItem;
}


class My::SaveListItem : public ListWidgetItem
{
public:
	SaveListItem(const std::wstring& name) {
		info.load(name);
	}
	~SaveListItem() override = default;

	void onPaint(RECT rect, ItemFlag, bool isFocused) override {
		D3DCOLOR dwColor = isFocused ? D3DCOLOR_XRGB(50, 50, 115) : D3DCOLOR_XRGB(66, 66, 132);
		engine.drawRect(rect, dwColor);

		RECT textRect = rect;
		textRect.left += 2;
		textRect.right -= 2;
		textRect.top += 2;
		textRect.bottom -= 2;
		engine.g_pFontSmall->DrawText(engine.g_pSprite, info.saveName.c_str(), -1, &textRect, DT_LEFT | DT_TOP, 0xffffffff);
		engine.g_pFontVerySmall->DrawText(engine.g_pSprite, info.saveNameInFile.c_str(), -1, &textRect, DT_LEFT | DT_BOTTOM, 0xffbbbbbb);
	}

	SaveInfo info;
};