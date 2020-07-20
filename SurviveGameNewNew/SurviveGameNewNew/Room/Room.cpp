#include "Room.h"

using namespace My;

void Room::onLogic() {
	int mouseX = engine.mouseX, mouseY = engine.mouseY;	//得到鼠标xy

	if (!engine.isKey(VK_LBUTTON) || engine.isKeyPressed(VK_LBUTTON)) {	//如果没有按下左键，或者刚按下左键
		//得到鼠标悬停在哪个控件上面
#ifdef DEBUG_WIDGET
		if (mouseAtWidget)
			mouseAtWidget->isMouseAtWidget = false;
#endif
		mouseAtWidget = nullptr;
		for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {	//反向遍历控件
			Widget* widget = *it;
			if (mouseX >= widget->wndX && mouseX <= widget->wndX + widget->w
				&& mouseY >= widget->wndY && mouseY <= widget->wndY + widget->h) {	//如果鼠标在控件范围内
				widget->getMouseAtWidget(&mouseAtWidget, mouseX, mouseY);	//调用控件的getMouseAtWidget
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

	if (mouseAtWidget) {
		//onMouseMove
		if (mouseX != mouseXBefore || mouseY != mouseYBefore) {
			Mouse mouse = Mouse::None;
			if (engine.isKey(VK_LBUTTON))
				mouse = mouse | Mouse::Left;
			if (engine.isKey(VK_MBUTTON))
				mouse = mouse | Mouse::Middle;
			if (engine.isKey(VK_RBUTTON))
				mouse = mouse | Mouse::Right;

			MouseMoveEvent ev;
			ev.button = mouse;
			ev.mouseX = mouseX - mouseAtWidget->wndX;
			ev.mouseY = mouseY - mouseAtWidget->wndY;
			if (mouse != Mouse::None || mouseAtWidget->isMouseTracking)
				mouseAtWidget->onMouseMove(&ev);
		}
	}
	mouseXBefore = mouseX;
	mouseYBefore = mouseY;


	//调用控件的onLogic
	for (Widget* widget : widgets)
		widget->onLogic();
}

void Room::onRender() {
	//调用控件的onRender
	RenderEvent ev;
	for (Widget* widget : widgets)
		widget->onRender(&ev);
}

void Room::onDestroy() {
	for (Widget* widget : widgets) {
		widget->onDestroy();
		delete widget;
	}
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