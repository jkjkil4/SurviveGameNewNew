#pragma once

#include "../NameSpace.h"
#include "../Class/Event.h"
#include "../Class/OperationClass.h"

#include "../Class/TextureManager.h"

#include "../utility.h"

#include "../Game/Data.h"
#include "../Game/Shader.h"

namespace My {
	class Widget;
}

//#define DEBUG_WIDGET

class My::Widget : public Object
{
public:
	Widget(int w, int h, Align align = Align::None, Widget* parent = nullptr);
	~Widget() override = default;

	virtual void onLogic();	//�ؼ����߼�����
	void setNeedLogic(bool flag);
	bool needLogic = false;

	void onRender(RenderEvent* ev);	//�ؼ�����Ⱦ
	virtual void onSelfRender(int, int) {}	//�ؼ��������Ⱦ

	void onDestroy();	//�ؼ�����

	void getMouseAtWidget(Widget** pMouseAtWidget, int mouseX, int mouseY);	//�õ������ͣ�Ŀؼ�
	virtual void onMousePressed(MouseEvent*) {}
	virtual void onMouseMove(MouseEvent*) {}
	virtual void onMouseReleased(MouseEvent*) {}
	bool isMouseTracking = false;

	virtual void onKeyPressed(KeyEvent*) {}
	virtual void onKeyReleased(KeyEvent*) {}

	virtual void onTextInput(std::wstring&) {}

	void setVisibleOperation(OperationClass* oper, int* pVisibleNum);
	bool isVisible();
	OperationClass* oper = nullptr;
	int* pVisibleNum = nullptr;

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

	LPCWSTR cursorShape = IDC_ARROW;	//�����ʽ

	bool isMouseAtWidget = false;
	bool isFocusWidget = false;

};