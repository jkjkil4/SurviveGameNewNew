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

	virtual void onLogic();		//逻辑处理
	virtual void onRender();	//渲染

	virtual void onDestroy();	//销毁

	void evResized();	//窗口大小改变事件
	void evKey(KeyEvent* ev);
	void evTextInput(std::wstring& input);

	virtual void onKeyPressed(KeyEvent* ev) {}
	virtual void onKeyReleased(KeyEvent* ev) {}

	void addWidget(Widget* widget);
	void removeWidget(Widget* widget);
	std::vector<Widget*> widgets;

	Widget* focusWidget = nullptr;	//焦点控件
	Widget* mouseAtWidget = nullptr;	//鼠标悬停的控件
	
	int mouseXBefore = -1, mouseYBefore = -1;

	virtual void setVisibleNum(int num) { visibleNum = num; }
	int visibleNum = -1;
};