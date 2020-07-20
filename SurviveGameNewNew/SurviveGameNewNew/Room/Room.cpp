#include "Room.h"

using namespace My;

void Room::onLogic() {
	//得到鼠标悬停在哪个控件上面
	Widget* mouseAtWidget = nullptr;
	int mouseX = engine.mouseX, mouseY = engine.mouseY;	//得到鼠标xy
	for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {	//反向遍历控件
		Widget* widget = *it;
		if (mouseX >= widget->wndX && mouseY <= widget->wndX + widget->w
			&& mouseY >= widget->wndY && mouseY <= widget->wndY + widget->h) {	//如果鼠标在子控件范围内
			widget->getMouseAtWidget(&mouseAtWidget, mouseX, mouseY);	//调用子控件的该函数
			break;
		}
	}


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