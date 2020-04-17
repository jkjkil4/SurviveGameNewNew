#include "MyWidget.h"

using namespace std;

MyWidget::MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget** focusWidget, MyWidget* parent) {
	this->e = e;
	this->parent = parent;
	this->g_pTexture = g_pTexture;
	this->pTextureInfo = pTextureInfo;
	this->focusWidget = focusWidget;
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
MyWidget::MyWidget(MyEngine* e, int w, int h, MyWidget** focusWidget, MyWidget* parent) {
	this->e = e;
	this->w = w;
	this->h = h;
	this->focusWidget = focusWidget;
	this->parent = parent;
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
void MyWidget::useRenderTarget() {
	safeRelease(g_pRenderTexture);
	safeRelease(g_pRenderSurface);
	e->g_pDevice->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pRenderTexture, NULL);
	g_pRenderTexture->GetSurfaceLevel(0, &g_pRenderSurface);
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
	if (pVisible)
		return visible == *pVisible;
	return true;
}

void MyWidget::onRender(LPD3DXSPRITE g_pSprite, int targetX, int targetY, int a, int r, int g, int b) {
	//绘制控件的贴图
	int renderX = wndX - targetX, renderY = wndY - targetY;
	if (g_pTexture)
		g_pSprite->Draw(g_pTexture, nullptr, &D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3((float)(renderX), (float)(renderY), 0), D3DCOLOR_XRGB(r, g, b));

	//继承类中的绘制
	_onRender(g_pSprite, renderX, renderY);

	//如果有Target的话，则设置
	LPDIRECT3DSURFACE9 g_pOldTarget = nullptr;
	if (g_pRenderSurface) {
		g_pSprite->End();
		e->g_pDevice->GetRenderTarget(0, &g_pOldTarget);
		e->g_pDevice->SetRenderTarget(0, g_pRenderSurface);
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		e->g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	}

	//子控件的绘制
	int childTargetX = g_pRenderSurface ? wndX : targetX;
	int childTargetY = g_pRenderSurface ? wndY : targetY;
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		if (w->isVisible())
			w->onRender(g_pSprite, childTargetX, childTargetY, a, r, g, b);
	}

	//还原Target
	if (g_pOldTarget) {
		g_pSprite->End();
		e->g_pDevice->SetRenderTarget(0, g_pOldTarget);
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		g_pSprite->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), 
			&D3DXVECTOR3((float)(childTargetX - targetX), (float)(childTargetY - targetY), 0), 0xffffffff);
	}
}
inline void MyWidget::_onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY){}
void MyWidget::onDestroy() {
	for (auto it = childs.begin(); it < childs.end(); it++) {
		MyWidget* w = *it;
		w->onDestroy();
		safeDelete(w);
	}
	safeRelease(g_pRenderTexture);
	safeRelease(g_pRenderSurface);
}

void MyWidget::mouseEvent(MyMouseEvent ev) {
	if (childs.size() > 0) {
		for (auto it = childs.rbegin(); it < childs.rend(); it++) {
			MyWidget* child = *it;
			if (!child->isVisible())
				continue;
			int localX = ev.x - child->realX;
			int localY = ev.y - child->realY;
			if (localX >= 0 && localX <= child->w && localY >= 0 && localY <= child->h) {
				child->mouseEvent(MyMouseEvent(ev.type, ev.mouse, localX, localY, ev.focusWidget));
				return;
			}
		}
	}
	if (ev.mouse == VK_LBUTTON && ev.type == MouseFlags::Press)
		*ev.focusWidget = this;
	_mouseEvent(ev);
}
inline void MyWidget::_mouseEvent(MyMouseEvent ev) {}

void MyWidget::mouseCheckAtEvent(int mouseX, int mouseY, MyWidget** mouseWidget) {
	for (auto it = childs.rbegin(); it < childs.rend(); it++) {
		MyWidget* child = *it;
		if (!child->isVisible())
			continue;
		int localX = mouseX - child->realX;
		int localY = mouseY - child->realY;
		if (localX >= 0 && localX <= child->w && localY >= 0 && localY <= child->h) {
			child->mouseCheckAtEvent(localX, localY, mouseWidget);
			return;
		}
	}
	*mouseWidget = this;
	isMouseAt = true;
}

void MyWidget::charEvent(wstring wstr) {
	_charEvent(wstr);
}
inline void MyWidget::_charEvent(wstring wstr) {}

void MyWidget::keyboardEvent(int key) {
	_keyboardEvent(key);
}
inline void MyWidget::_keyboardEvent(int key) {}
