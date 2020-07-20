#include "Room.h"

using namespace My;

void Room::onLogic() {
	//�õ������ͣ���ĸ��ؼ�����
	Widget* mouseAtWidget = nullptr;
	int mouseX = engine.mouseX, mouseY = engine.mouseY;	//�õ����xy
	for (auto it = widgets.rbegin(); it < widgets.rend(); it++) {	//��������ؼ�
		Widget* widget = *it;
		if (mouseX >= widget->wndX && mouseY <= widget->wndX + widget->w
			&& mouseY >= widget->wndY && mouseY <= widget->wndY + widget->h) {	//���������ӿؼ���Χ��
			widget->getMouseAtWidget(&mouseAtWidget, mouseX, mouseY);	//�����ӿؼ��ĸú���
			break;
		}
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