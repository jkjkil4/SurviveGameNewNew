
#ifndef _MYWIDGET_H
#define _MYWIDGET_H


#include "../utility.h"
#include "../MyEngine.h"
#include "../MyNameSpace.h"

class MyWidget;

class MyMouseEvent
{
public:
	explicit MyMouseEvent(int type, int mouse, int x, int y, MyWidget** focusWidget) {
		this->type = type;
		this->mouse = mouse;
		this->x = x;
		this->y = y;
		this->focusWidget = focusWidget;
	}
	int type = 0;
	int mouse = 0;
	int x = 0;
	int y = 0;
	MyWidget** focusWidget = nullptr;
};

class MyWidget
{
public:
	explicit MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget** focusWidget = nullptr, MyWidget* parent = nullptr);
	explicit MyWidget(MyEngine* e, int w, int h, MyWidget** focusWidget = nullptr, MyWidget* parent = nullptr);
	virtual ~MyWidget();

	void move(int x, int y);
	void resize(int w, int h);
	void setAlign(int flags);
	void updatePos(int alignW, int alignH);

	bool isVisible();

	void onRender(LPD3DXSPRITE g_pSprite, int a = 255, int r = 255, int g = 255, int b = 255);
	virtual inline void _onRender(LPD3DXSPRITE g_pSprite);
	void onDestroy();

	void mouseEvent(MyMouseEvent ev);
	virtual inline void _mouseEvent(MyMouseEvent ev);

	void charEvent(std::wstring wstr);
	virtual inline void _charEvent(std::wstring wstr);

	void keyboardEvent(int key);
	virtual inline void _keyboardEvent(int key);

	//-----------------------------------------------
	MyEngine* e = nullptr;
	MyWidget* parent = nullptr;
	//���뷽��
	int alignFlags = 0;
	//���ڶ��뷽����˵������Ϳ��
	int x = 0, y = 0;
	int w = 10, h = 10;
	//����������
	int realX = 0, realY = 0;
	//����ڴ��ڵ�����
	int wndX = 0, wndY = 0;
	//��ͼ
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
	D3DXIMAGE_INFO* pTextureInfo = nullptr;
	//�Ƿ�ɼ�
	int* pVisible = nullptr;
	int visible = 0;
	//�ӿؼ�
	std::vector<MyWidget*> childs;
	//����ؼ�
	MyWidget** focusWidget = nullptr;
};

#endif //_MYWIDGET_H