#include "MyWidget.h"

MyWidget::MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget* parent) {
	if (parent && parent != this) {
		parent->childs.push_back(this);
	}
	this->e = e;
	this->parent = parent;
	this->g_pTexture = g_pTexture;
	this->pTextureInfo = pTextureInfo;
	w = pTextureInfo->Width;
	h = pTextureInfo->Height;
	parent ? updatePos(parent->w, parent->h) : updatePos(e->viewW, e->viewH);
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
}

void MyWidget::onRender(LPD3DXSPRITE g_pSprite, int a, int r, int g, int b, int offX, int offY) {
	if (g_pTexture)
		g_pSprite->Draw(g_pTexture, nullptr, &D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3((float)(realX + offX), (float)(realY + offY), 0), D3DCOLOR_XRGB(r, g, b));
	for (auto it = childs.begin(); it < childs.end(); it++)
		(*it)->onRender(g_pSprite, a, r, g, b, offX + realX, offY + realY);
}
void MyWidget::onDestroy() {
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		w->onDestroy();
		safeDelete(w);
	}
}
