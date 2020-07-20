#include "Room.h"

using namespace My;

void Room::onLogic() {
	Widget* mouseAtWidget = nullptr;	//鼠标悬停的控件


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