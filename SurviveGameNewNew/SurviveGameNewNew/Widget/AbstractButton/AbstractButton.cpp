#include "AbstractButton.h"

using namespace My;

void AbstractButton::onMouseReleased(MouseEvent* ev) {
	if (ev->button == Mouse::Left && isChecking()) {
		if (slot)
			(slot->*slotFunc)(this);
	}
}


void AbstractButton::setSlot(Object* slot, PushButtonFunc slotFunc) {
	this->slot = slot;
	this->slotFunc = slotFunc;
}


bool AbstractButton::isChecking() {
	int mouseX = engine.mouseX, mouseY = engine.mouseY;
	return getIsMouseAtWidget() && mouseX >= wndX && mouseX <= wndX + w && mouseY >= wndY && mouseY <= wndY + h;
}

bool AbstractButton::isHolding() {
	return getIsMouseAtWidget() && engine.isKey(VK_LBUTTON);
}
