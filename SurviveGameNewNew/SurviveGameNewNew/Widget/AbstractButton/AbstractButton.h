#pragma once

#include "../Widget.h"

namespace My {
	class AbstractButton;
}

class My::AbstractButton : public Widget
{
public:
	AbstractButton(int w, int h, Align align = Align::None, Widget* parent = nullptr)
		: Widget(w, h, align, parent) {}
	~AbstractButton() override = default;

	void onMouseReleased(MouseEvent* ev) override;

	bool isChecking();
	bool isHolding();
};
