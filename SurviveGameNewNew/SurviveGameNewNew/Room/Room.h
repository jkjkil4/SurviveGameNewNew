#pragma once

#include "../Widget/ImageLabel/ImageLabel.h"
#include "../Widget/TextLabel/TextLabel.h"

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

	void addWidget(Widget* widget);
	void removeWidget(Widget* widget);
	std::vector<Widget*> widgets;

	Widget* focusWidget = nullptr;	//����ؼ�
	Widget* mouseAtWidget = nullptr;	//�����ͣ�Ŀؼ�
	
	int mouseXBefore = -1, mouseYBefore = -1;
};