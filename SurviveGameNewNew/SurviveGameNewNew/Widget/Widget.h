#pragma once

#include "../NameSpace.h"
#include "../Class/Event.h"

#include "../Class/TextureManager.h"

#include "../utility.h"

namespace My {
	class Widget;
}

class My::Widget : public Object
{
public:
	Widget(int w, int h, Align align, Widget* parent = nullptr);
	~Widget() override = default;

	void onLogic();

	void onRender(RenderEvent* ev);
	virtual void onSelfRender(int, int) {}

	void onDestroy();

	void updatePos();

	void createRenderTarget();
	void destroyRenderTarget();
	bool hasTarget();
	LPTexture g_pTargetTexture = nullptr;
	LPSurface g_pTargetSurface = nullptr;
	TextureManager* targetManager = nullptr;

	void setParent(Widget* parent);
	void addChild(Widget* child);
	void removeChild(Widget* child);
	Widget* parent = nullptr;
	std::vector<Widget*> childs;

	void resize(int w, int h);
	int w = 10, h = 10;

	void move(int x, int y);
	int x = 0, y = 0;
	int realX = 0, realY = 0;
	int wndX = 0, wndY = 0;

	void setAlign(Align align);
	Align align = Align::None;

	D3DCOLOR col = rand() % 0xffffff + 0xff000000;
};