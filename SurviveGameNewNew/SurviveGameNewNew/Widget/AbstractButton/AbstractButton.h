#pragma once

#include "../Widget.h"

namespace My {
	class AbstractButton;
	typedef void(Object::* ButtonFunc)(AbstractButton*);
}


class My::AbstractButton : public Widget
{
public:
	AbstractButton(int w, int h, Align align = Align::None, Widget* parent = nullptr)
		: Widget(w, h, align, parent) {}
	~AbstractButton() override = default;

	void setSlot(Object* slot, ButtonFunc slotMemberFunc);
	Object* slot = nullptr;
	ButtonFunc slotMemberFunc = nullptr;
	bool isEnabled = true;

	void onMouseReleased(MouseEvent* ev) override;

	bool isChecking();
	bool isHolding();
};
