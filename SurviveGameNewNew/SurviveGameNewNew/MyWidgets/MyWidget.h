
#ifndef _MYWIDGET_H
#define _MYWIDGET_H


#include "../utility.h"
#include "../MyEngine.h"
#include "../MyNameSpace.h"

class MyWidget
{
public:
	explicit MyWidget(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget* parent = nullptr);
	virtual ~MyWidget();

	void move(int x, int y);
	void resize(int w, int h);
	void setAlign(int flags);
	void updatePos(int alignW, int alignH);

	void onRender(LPD3DXSPRITE g_pSprite, int a = 255, int r = 255, int g = 255, int b = 255, int offX = 0, int offY = 0);
	void onDestroy();

	virtual void mouseEvent(int type, int mouse, int x, int y);

	//-----------------------------------------------
	MyEngine* e = nullptr;
	MyWidget* parent = nullptr;
	//对齐方向
	int alignFlags = 0;
	//对于对齐方向来说的坐标和宽度
	int x = 0, y = 0;
	int w = 10, h = 10;
	//真正的坐标
	int realX = 0, realY = 0;
	//贴图
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
	D3DXIMAGE_INFO* pTextureInfo;
	//子控件
	std::vector<MyWidget*> childs;
};

#endif //_MYWIDGET_H