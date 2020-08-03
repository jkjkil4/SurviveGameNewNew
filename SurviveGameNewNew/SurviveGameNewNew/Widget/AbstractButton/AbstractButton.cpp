#include "AbstractButton.h"

using namespace My;

void AbstractButton::onMouseReleased(MouseEvent* ev) {
	if (ev->button == Mouse::Left && isChecking()) {
		if (slotMemberFunc)
			(slot->*slotMemberFunc)(this);
	}
}


void AbstractButton::setSlot(Object* slot, ButtonFunc slotMemberFunc) {
	this->slot = slot;
	this->slotMemberFunc = slotMemberFunc;
}


bool AbstractButton::isChecking() {
	int mouseX = engine.mouseX, mouseY = engine.mouseY;
	return isMouseAtWidget && mouseX >= wndX && mouseX <= wndX + w && mouseY >= wndY && mouseY <= wndY + h;
}

bool AbstractButton::isHolding() {
	return isMouseAtWidget && engine.isKey(VK_LBUTTON);
}
