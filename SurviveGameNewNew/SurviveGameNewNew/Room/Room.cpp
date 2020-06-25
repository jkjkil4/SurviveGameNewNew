#include "Room.h"

using namespace My;

void Room::onLogic() {

}

void Room::onRender() {
	//调用控件的onRender
	RenderEvent ev;
	for (auto it = widgets.begin(); it < widgets.end(); it++)
		(*it)->onRender(&ev);
}

void Room::onDestroy() {

}


void Room::evResized() {
	for (auto widget : widgets)
		widget->updatePos();
}


void Room::addWidget(Widget* widget) {
	widgets.push_back(widget);
}

void Room::removeWidget(Widget* widget) {
	for (auto it = widgets.begin(); it < widgets.end(); it++) {
		if (*it == widget) {
			widgets.erase(it);
			break;
		}
	}
}