#include "AbstractButton.h"

using namespace My;

void AbstractButton::onLogic() {
	if (engine.isKeyReleased(VK_LBUTTON) && isChecking()) {
		std::cout << "��ť " << this << " ������" << std::endl;
	}

	Widget::onLogic();
}

bool AbstractButton::isChecking() {
	int mouseX = engine.mouseX, mouseY = engine.mouseY;
	return getIsMouseAtWidget() && mouseX >= wndX && mouseX <= wndX + w && mouseY >= wndY && mouseY <= wndY + h;
}

bool AbstractButton::isHolding() {
	return getIsMouseAtWidget() && engine.isKey(VK_LBUTTON);
}