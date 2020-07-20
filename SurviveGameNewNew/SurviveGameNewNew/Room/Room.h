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

	virtual void onLogic();		//逻辑处理
	virtual void onRender();	//渲染

	virtual void onDestroy();	//销毁

	void evResized();	//窗口大小改变事件

	void addWidget(Widget* widget);
	void removeWidget(Widget* widget);
	std::vector<Widget*> widgets;

	Widget* focusWidget = nullptr;	//焦点控件
	Widget* mouseAtWidget = nullptr;	//鼠标悬停的控件
	
	int mouseXBefore = -1, mouseYBefore = -1;
};