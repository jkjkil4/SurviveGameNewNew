#include "MyWidget.h"

MyWidget::MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget* parent) {
	this->e = e;
	this->parent = parent;
	this->g_pTexture = g_pTexture;
	this->pTextureInfo = pTextureInfo;
	w = pTextureInfo->Width;
	h = pTextureInfo->Height;
	if (parent) {
		parent->childs.push_back(this);
		updatePos(parent->w, parent->h);
	}
	else {
		updatePos(e->viewW, e->viewH);
	}
}
MyWidget::~MyWidget(){}

void MyWidget::move(int x, int y) {
	this->x = x;
	this->y = y;
	parent ? updatePos(parent->w, parent->h) : updatePos(e->viewW, e->viewH);
}
void MyWidget::resize(int w, int h) {
	this->w = w;
	this->h = h;
	parent ? updatePos(parent->w, parent->h) : updatePos(e->viewW, e->viewH);
	for (auto it = childs.begin(); it < childs.end(); it++)
		updatePos(w, h);
}
void MyWidget::setAlign(int flags) { 
	alignFlags = flags;
	parent ? updatePos(parent->w, parent->h) : updatePos(e->viewW, e->viewH);
}
void MyWidget::updatePos(int alignW, int alignH) {
	bool isLeft = alignFlags & AlignFlags::Left;
	bool isRight = alignFlags & AlignFlags::Right;
	bool isTop = alignFlags & AlignFlags::Top;
	bool isBottom = alignFlags & AlignFlags::Bottom;

	//x
	if (isLeft)
		realX = x;
	else if (isRight)
		realX = alignW - w - x;
	else
		realX = (alignW - w) / 2 + x;

	//y
	if (isTop)
		realY = y;
	else if (isBottom)
		realY = alignH - h - y;
	else
		realY = (alignH - h) / 2 + y;

	if (parent) {
		wndX = parent->wndX + realX;
		wndY = parent->wndY + realY;
	}
	else {
		wndX = realX;
		wndY = realY;
	}
	for (auto it = childs.begin(); it < childs.end(); it++)
		(*it)->updatePos(w, h);
}

bool MyWidget::isVisible() {
	if (visible)
		return *visible;
	return true;
}

void MyWidget::onRender(LPD3DXSPRITE g_pSprite, int a, int r, int g, int b) {
	if (g_pTexture)
		g_pSprite->Draw(g_pTexture, nullptr, &D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3((float)(wndX), (float)(wndY), 0), D3DCOLOR_XRGB(r, g, b));
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		if(w->isVisible())
			w->onRender(g_pSprite, a, r, g, b);
	}
	_onRender(g_pSprite, a, r, g, b);
}
void MyWidget::_onRender(LPD3DXSPRITE g_pSprite, int a, int r, int g, int b){}
void MyWidget::onDestroy() {
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		w->onDestroy();
		safeDelete(w);
	}
}

bool MyWidget::mouseEvent(int type, int mouse, int x, int y) {
	if (childs.size() > 0) {
		for (auto it = childs.rbegin(); it < childs.rend(); it++) {
			MyWidget* child = *it;
			if (!child->isVisible())
				continue;
			int localX = x - child->realX;
			int localY = y - child->realY;
			if (localX >= 0 && localX <= child->w && localY >= 0 && localY <= child->h) {
				if (child->mouseEvent(type, mouse, localX, localY))
					return true;
				return false;
			}
		}
	}
	return true;
}
