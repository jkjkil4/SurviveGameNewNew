#include "Room.h"

using namespace My;

void Room::onLogic() {
	if (!engine.isKey(VK_LBUTTON) || engine.isKeyPressed(VK_LBUTTON)) {
		//�õ������ͣ���ĸ��ؼ�����
#ifdef DEBUG_WIDGET
		if (mouseAtWidget)
			mouseAtWidget->isMouseAtWidget = false;
#endif
		mouseAtWidget = nullptr;
		int mouseX = engine.mouseX, mouseY = engine.mouseY;	//�õ����xy
		for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {	//��������ؼ�
			Widget* widget = *it;
			if (mouseX >= widget->wndX && mouseX <= widget->wndX + widget->w
				&& mouseY >= widget->wndY && mouseY <= widget->wndY + widget->h) {	//�������ڿؼ���Χ��
				widget->getMouseAtWidget(&mouseAtWidget, mouseX, mouseY);	//���ÿؼ���getMouseAtWidget
				break;
			}
		}
		if (engine.isKeyPressed(VK_LBUTTON)) {
			if (focusWidget)
				focusWidget->isFocusWidget = false;
			if (mouseAtWidget) {
				focusWidget = mouseAtWidget;
				focusWidget->isFocusWidget = true;
			}
			else focusWidget = nullptr;
		}
#ifdef DEBUG_WIDGET
		if (mouseAtWidget)
			mouseAtWidget->isMouseAtWidget = true;
#endif
	}


	//���ÿؼ���onLogic
	for (Widget* widget : widgets)
		widget->onLogic();
}

void Room::onRender() {
	//���ÿؼ���onRender
	RenderEvent ev;
	for (Widget* widget : widgets)
		widget->onRender(&ev);
}

void Room::onDestroy() {

}


void Room::evResized() {
	for (Widget* widget : widgets)
		widget->updatePos();
}


void Room::addWidget(Widget* widget) {
	widgets.push_back(widget);
	if (widget->parent) {
		widget->parent->removeChild(widget);
		widget->parent = nullptr;
	}
}

void Room::removeWidget(Widget* widget) {
	for (auto it = widgets.begin(); it < widgets.end(); it++) {
		if (*it == widget) {
			widgets.erase(it);
			break;
		}
	}
}