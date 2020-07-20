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

	virtual void onLogic();	//�ؼ����߼�����

	void onRender(RenderEvent* ev);	//�ؼ�����Ⱦ
	virtual void onSelfRender(int, int) {}	//�ؼ��������Ⱦ

	void onDestroy();	//�ؼ�����

	void updatePos();	//����λ��

	void createRenderTarget();	//ʹ��RenderTarget��ʹ�ó����ؼ��Ĳ��ֲ��ᱻ��ʾ
	void destroyRenderTarget();	//����RenderTarget
	bool hasTarget();	//�Ƿ���RenderTarget
	LPTexture g_pTargetTexture = nullptr;	//RenderTarget������
	LPSurface g_pTargetSurface = nullptr;
	TextureManager* targetManager = nullptr;

	void setParent(Widget* newParent);	//���ø��ؼ�
	void addChild(Widget* child);		//����ӿؼ�
	void removeChild(Widget* child);	//�Ƴ��ӿؼ�
	Widget* parent = nullptr;		//���ؼ�
	std::vector<Widget*> childs;	//�ӿؼ�

	void resize(int w, int h);	//�ı��С
	int w = 10, h = 10;		//���

	void move(int x, int y);	//�ƶ��ؼ�
	int x = 0, y = 0;		//��Ե�xy
	int realX = 0, realY = 0;	//���ڸ��ؼ���˵��xy
	int wndX = 0, wndY = 0;		//���ڴ�����˵��xy

	void setAlign(Align align);		//���ö��뷽ʽ
	Align align = Align::None;	//���뷽ʽ

};