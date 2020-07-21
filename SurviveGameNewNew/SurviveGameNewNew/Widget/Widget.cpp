#include "Widget.h"

#include "../Engine/Engine.h"

using namespace My;

Widget::Widget(int w, int h, Align align, Widget* parent)
	: parent(parent), w(w), h(h), align(align)
{
	if (parent) {	//����и��ؼ��Ļ�����ô����ǰ�ؼ���ָ����뵽 ���ؼ����ӿؼ��б� ��
		parent->addChild(this);
	}
	updatePos();	//����λ��
}


void Widget::onLogic() {
	for (Widget* child : childs)	//�ӿؼ����߼�����
		child->onLogic();
}

void Widget::setNeedLogic(bool flag) {
	needLogic = flag;
	if (flag && parent) {
		parent->setNeedLogic(true);
	}
}


void Widget::onRender(RenderEvent* ev) {
	//����ÿؼ����ɼ�����return
	if (!isVisible())
		return;

	//����ÿؼ���ȫ�ڸ��ؼ�֮�⣬��return
	if (parent)
		if (wndX + w < parent->wndX || wndX > parent->wndX + parent->w || wndY + h < parent->wndY || wndY > parent->wndY + parent->h)
			return;

	//�����Target��������
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
#ifdef DEBUG_WIDGET
	if (isMouseAtWidget || isFocusWidget) {
		engine.drawRestart();
		if (isMouseAtWidget)
			engine.drawRect(wndX - ev->targetX, wndY - ev->targetY, w, h, 0x44dd2222, 0x44dd2222, 0x44dd2222, 0x44dd2222);
		if (isFocusWidget)
			engine.drawRect(wndX - ev->targetX, wndY - ev->targetY, w, h, 0x4422dd22, 0x4422dd22, 0x4422dd22, 0x4422dd22);
	}
#endif
	
	//�ӿؼ��Ļ���
	for (Widget* child : childs)
		child->onRender(ev);

	//��ԭTarget
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
	destroyRenderTarget();	//����RenderTarget
	safeDelete(oper);

	for (Widget* child : childs) {	//�����ӿؼ�
		child->onDestroy();
		delete child;
	}
}


void Widget::getMouseAtWidget(Widget** pMouseAtWidget, int mouseX, int mouseY) {
	for (auto it = childs.rbegin(); it < childs.rend(); it++) {	//��������ӿؼ�
		Widget* child = *it;
		if (!child->isVisible())
			continue;
		if (mouseX >= child->wndX && mouseX <= child->wndX + child->w
			&& mouseY >= child->wndY && mouseY <= child->wndY + child->h) {	//���������ӿؼ���Χ��
			child->getMouseAtWidget(pMouseAtWidget, mouseX, mouseY);	//�����ӿؼ��ĸú���
			return;
		}
	}
	*pMouseAtWidget = this;	//�������ͣ�Ŀؼ�����Ϊ�Լ�
}


void Widget::setVisibleOperation(OperationClass* oper, int* pVisibleNum) {
	this->oper = oper;
	this->pVisibleNum = pVisibleNum;
}

bool Widget::isVisible() {
	if (oper)
		return oper->check(pVisibleNum);
	return true;
}


void Widget::updatePos() {
	int parentW = parent ? parent->w : engine.getViewW();	//�õ����ؼ��Ŀ�� (���û�и��ؼ���Ϊ���ڿ��)
	int parentH = parent ? parent->h : engine.getViewH();	//�õ����ؼ��ĸ߶� (...�߶�)
	int parentX = parent ? parent->wndX : 0;	//�õ����ؼ���x (���û�и��ؼ���Ϊ0)
	int parentY = parent ? parent->wndY : 0;	//�õ����ؼ���y (...)

	realX = (align & Align::Left) ? x : ((align & Align::Right) ? parentW - x - w : (parentW - w) / 2 + x);
	realY = (align & Align::Top) ? y : ((align & Align::Bottom) ? parentH - y - h : (parentH - h) / 2 + y);

	wndX = parentX + realX;
	wndY = parentY + realY;

	for (Widget* child : childs)
		child->updatePos();
}



void Widget::createRenderTarget() {
	destroyRenderTarget();	//����RenderTarget

	TextureManagerFunc releaseFunc = [](void* sendObj) {	//������RenderTargetʱ���õĺ���
		Widget* obj = (Widget*)sendObj;
		safeRelease(obj->g_pTargetSurface);
		safeRelease(obj->g_pTargetTexture);
	};
	TextureManagerFunc resetFunc = [](void* sendObj) {	//�ڴ���RenderTargetʱ���õĺ���
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


void Widget::setParent(Widget* newParent) {
	if (parent)		//����и��ؼ�
		parent->removeChild(this);	//����ǰ�ؼ��� ���ؼ����ӿؼ��б� ���Ƴ�
	parent = newParent;	//�����µĸ��ؼ�
	newParent->addChild(this);	//����ǰ�ؼ���ӵ� �µĸ��ؼ����ӿؼ��б� ��
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