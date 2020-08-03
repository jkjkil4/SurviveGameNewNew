#pragma once

#include "../Widget/Widget.h"

#include "../utility.h"


namespace My {
	class Room;
}

class My::Room : public Object
{
public:
	~Room() override = default;

	virtual void onLogic();		//�߼�����
	virtual void onRender();	//��Ⱦ

	virtual void onDestroy();	//����

	void evResized();	//���ڴ�С�ı��¼�
	void evKey(KeyEvent* ev);
	void evTextInput(std::wstring& input);

	virtual void onKeyPressed(KeyEvent* ev) {}
	virtual void onKeyReleased(KeyEvent* ev) {}

	void addWidget(Widget* widget);
	void removeWidget(Widget* widget);
	std::vector<Widget*> widgets;

	Widget* focusWidget = nullptr;	//����ؼ�
	Widget* mouseAtWidget = nullptr;	//�����ͣ�Ŀؼ�
	
	int mouseXBefore = -1, mouseYBefore = -1;

	virtual void setVisibleNum(int num) { visibleNum = num; }
	int visibleNum = -1;
};