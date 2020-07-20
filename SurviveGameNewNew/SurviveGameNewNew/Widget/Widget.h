#pragma once

#include "../NameSpace.h"
#include "../Class/Event.h"

#include "../Class/TextureManager.h"

#include "../Game/Data.h"

#include "../utility.h"

namespace My {
	class Widget;
}

class My::Widget : public Object
{
public:
	Widget(int w, int h, Align align = Align::None, Widget* parent = nullptr);
	~Widget() override = default;

	virtual void onLogic();	//控件的逻辑处理

	void onRender(RenderEvent* ev);	//控件的渲染
	virtual void onSelfRender(int, int) {}	//控件自身的渲染

	void onDestroy();	//控件销毁

	void updatePos();	//更新位置

	void createRenderTarget();	//使用RenderTarget，使得超出控件的部分不会被显示
	void destroyRenderTarget();	//销毁RenderTarget
	bool hasTarget();	//是否有RenderTarget
	LPTexture g_pTargetTexture = nullptr;	//RenderTarget三件套
	LPSurface g_pTargetSurface = nullptr;
	TextureManager* targetManager = nullptr;

	void setParent(Widget* newParent);	//设置父控件
	void addChild(Widget* child);		//添加子控件
	void removeChild(Widget* child);	//移除子控件
	Widget* parent = nullptr;		//父控件
	std::vector<Widget*> childs;	//子控件

	void resize(int w, int h);	//改变大小
	int w = 10, h = 10;		//宽高

	void move(int x, int y);	//移动控件
	int x = 0, y = 0;		//相对的xy
	int realX = 0, realY = 0;	//对于父控件来说的xy
	int wndX = 0, wndY = 0;		//对于窗口来说的xy

	void setAlign(Align align);		//设置对齐方式
	Align align = Align::None;	//对齐方式

};