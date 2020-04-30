
#ifndef _MYWIDGET_H
#define _MYWIDGET_H


#include "../utility.h"
#include "../MyEngine.h"
#include "../MyNameSpace.h"
#include "../MyClasses/MyExpr.h"

class MyMouseEvent
{
public:
	explicit MyMouseEvent(int type, int mouse, int x, int y) {
		this->type = type;
		this->mouse = mouse;
		this->x = x;
		this->y = y;
	}
	int type = 0;
	int mouse = 0;
	int x = 0;
	int y = 0;
};



/*
	��Ҫ�ͷŵĶ���
	g_pRenderTexture
	g_pRenderSurface
	vbRectangle
*/
class MyWidget
{
public:
	explicit MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget** focusWidget = nullptr, MyWidget* parent = nullptr);
	explicit MyWidget(MyEngine* e, int w, int h, MyWidget** focusWidget = nullptr, MyWidget* parent = nullptr);
	virtual ~MyWidget() = default;

	void move(int x, int y);
	void resize(int w, int h);

	void setAlign(int flags);

	void useRenderTarget();

	void updatePos(int alignW, int alignH);

	bool isVisible();

	void onRender(LPD3DXSPRITE g_pSprite, int targetX = 0, int targetY = 0, int a = 255, int r = 255, int g = 255, int b = 255);
	virtual inline void _onRender(LPD3DXSPRITE, int, int) {}

	void onDestroy();

	void mouseEvent(MyMouseEvent ev);
	virtual inline void _mouseEvent(MyMouseEvent) {}

	void wheelEvent(int mouseX, int mouseY, int delta);
	virtual inline void _wheelEvent(int, int, int) {}

	void mouseCheckAtEvent(int mouseX, int mouseY, MyWidget** mouseWidget);

	void charEvent(std::wstring wstr);
	virtual inline void _charEvent(std::wstring) {}

	void keyboardEvent(int key);
	virtual inline void _keyboardEvent(int) {}

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
	//����Ͷ�Ӧ�ı���(������������
	LPDIRECT3DTEXTURE9 g_pRenderTexture = nullptr;
	LPDIRECT3DSURFACE9 g_pRenderSurface = nullptr;

	//�Ƿ�ɼ�
	int* pVisible = nullptr;
	int visible = 0;
	MyExpr expr;
	//����Ƿ��ڸÿؼ���
	bool isMouseAt = false;

	//�Ƿ����wheelEvent
	bool isAcceptWheelEvent = false;

	//�ӿؼ�
	std::vector<MyWidget*> childs;
	//����ؼ�
	MyWidget** focusWidget = nullptr;
};

#endif //_MYWIDGET_H