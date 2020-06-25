#include "Widget.h"

#include "../Engine/Engine.h"

using namespace My;

Widget::Widget(int w, int h, Align align, Widget* parent)
	: parent(parent), w(w), h(h), align(align)
{
	if (parent) {
		parent->addChild(this);
	}
	updatePos();
}


void Widget::onLogic() {
	for (auto it = childs.begin(); it < childs.end(); it++)
		(*it)->onLogic();
}

void Widget::onRender(RenderEvent* ev) {
	//如果该控件完全在父控件之外，则return
	if (parent)
		if (wndX + w < parent->wndX || wndX > parent->wndX + parent->w || wndY + h < parent->wndY || wndY > parent->wndY + parent->h)
			return;

	//如果有Target，则设置
	LPSurface g_pOldTarget = nullptr;
	int oldTargetX = ev->targetX, oldTargetY = ev->targetY;
	if (hasTarget()) {
		engine.g_pSprite->End();
		engine.g_pDevice->GetRenderTarget(0, &g_pOldTarget);
		engine.g_pDevice->SetRenderTarget(0, g_pTargetSurface);
		engine.g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		engine.g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	
		ev->targetX = wndX;
		ev->targetY = wndY;
	}

	onSelfRender(wndX - ev->targetX, wndY - ev->targetY);
	
	//子控件的绘制
	for (auto it = childs.begin(); it < childs.end(); it++)
		(*it)->onRender(ev);

	//还原Target
	if (g_pOldTarget) {
		ev->targetX = oldTargetX;
		ev->targetY = oldTargetY;

		engine.g_pSprite->End();
		engine.g_pDevice->SetRenderTarget(0, g_pOldTarget);
		engine.g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		engine.g_pSprite->Draw(g_pTargetTexture, nullptr, &D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3((float)(wndX - ev->targetX), (float)(wndY - ev->targetY), 0), 0xffffffff);
	}
}


void Widget::onDestroy() {
	destroyRenderTarget();
}


void Widget::updatePos() {
	int parentW = parent ? parent->w : engine.getViewW();
	int parentH = parent ? parent->h : engine.getViewH();
	int parentX = parent ? parent->wndX : 0;
	int parentY = parent ? parent->wndY : 0;

	realX = (align & Align::Left) ? x : ((align & Align::Right) ? parentW - x - w : (parentW - w) / 2 + x);
	realY = (align & Align::Top) ? y : ((align & Align::Bottom) ? parentH - y - h : (parentH - h) / 2 + y);

	wndX = parentX + realX;
	wndY = parentY + realY;

	for (auto it = childs.begin(); it < childs.end(); it++)
		(*it)->updatePos();
}



void Widget::createRenderTarget() {
	destroyRenderTarget();

	TextureManagerFunc releaseFunc = [](void* sendObj) {
		Widget* obj = (Widget*)sendObj;
		safeRelease(obj->g_pTargetSurface);
		safeRelease(obj->g_pTargetTexture);
	};
	TextureManagerFunc resetFunc = [](void* sendObj) {
		Widget* obj = (Widget*)sendObj;
		engine.g_pDevice->CreateTexture(obj->w, obj->h, 1, D3DUSAGE_RENDERTARGET, 
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, 
			&obj->g_pTargetTexture, NULL);
		obj->g_pTargetTexture->GetSurfaceLevel(0, &obj->g_pTargetSurface);
	};
	targetManager = new TextureManager(releaseFunc, resetFunc, this);
	targetManager->resetTexture();
}

void Widget::destroyRenderTarget() {
	if (hasTarget()) {
		targetManager->releaseTexture();
		TextureManager::removeManager(targetManager);
		safeDelete(targetManager);
	}
}

bool Widget::hasTarget() {
	return targetManager;
}


void Widget::setParent(Widget* parent) {
	this->parent->removeChild(this);
	this->parent = parent;
	parent->addChild(this);
}

void Widget::addChild(Widget* child) {
	childs.push_back(child);
}

void Widget::removeChild(Widget* child) {
	for (auto it = childs.begin(); it < childs.end(); it++) {
		if (*it == child) {
			childs.erase(it);
			break;
		}
	}
}


void Widget::resize(int w, int h) {
	this->w = w;
	this->h = h;
	updatePos();
}


void Widget::move(int x, int y) {
	this->x = x;
	this->y = y;
	updatePos();
}


void Widget::setAlign(Align align) {
	this->align = align;
	updatePos();
}