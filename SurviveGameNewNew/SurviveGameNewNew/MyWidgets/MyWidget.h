
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

/*
#define AlignFlag_left		1
#define AlignFlag_right		2
#define AlignFlag_top		4
#define AlignFlag_bottom	8

class MyViewControl
{
public:
	explicit MyViewControl(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture) {
		this->e = e;
		this->g_pTexture = g_pTexture;
	}
	bool checkMouseAt(int mouseX, int mouseY) {
		if (tempMouseX != mouseX || tempMouseY != mouseY) {
			bool left = flags & AlignFlag_left;
			bool right = flags & AlignFlag_right;
			bool top = flags & AlignFlag_top;
			bool bottom = flags & AlignFlag_bottom;

			int rectLeft;
			if (left) {
				rectLeft = x;
			}
			else if (right) {
				rectLeft = e->viewW - x - w;
			}
			else {
				rectLeft = (e->viewW - w) / 2 + x;
			}
			mouseX -= rectLeft;

			int rectTop;
			if (top) {
				rectTop = y;
			}
			else if (bottom) {
				rectTop = e->viewH - y - h;
			}
			else {
				rectTop = (e->viewH - h) / 2 + y;
			}
			mouseY -= rectTop;

			tempMouseX = mouseX;
			tempMouseY = mouseY;
			if (mouseX >= 0 && mouseY >= 0 && mouseX <= w && mouseY <= h) {
				tempIsMouseAt = true;
			} else {
				tempIsMouseAt = false;
			}
		}
		return tempIsMouseAt;
	}
	void move(int x, int y) {
		int tempMouseX = -1;
		int tempMouseY = -1;
		this->x = x;
		this->y = y;
	}
	void resize(int w, int h) {
		int tempMouseX = -1;
		int tempMouseY = -1;
		this->w = w;
		this->h = h;
	}

	void onRender(LPD3DXSPRITE g_pSprite, int r, int g, int b) {
		int posX = 0, posY = 0;
		bool left = flags & AlignFlag_left;
		bool right = flags & AlignFlag_right;
		bool top = flags & AlignFlag_top;
		bool bottom = flags & AlignFlag_bottom;

		if (left) {
			posX = x;
		} else if (right) {
			posX = e->viewW - x - w;
		} else {
			posX = (e->viewW - w) / 2 + x;
		}

		if (top) {
			posY = y;
		} else if (bottom) {
			posY = e->viewH - y - h;
		} else {
			posY = (e->viewH - h) / 2 + y;
		}

		if (clickable) {
			if (checkMouseAt(e->mouseX, e->mouseY)) {
				r = (int)(r * 0.8);
				g = (int)(g * 0.8);
				b = (int)(b * 0.8);
			}
		}
		g_pSprite->Draw(g_pTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3((float)posX, (float)posY, 0), D3DCOLOR_XRGB(r, g, b));
	}
	
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	int tempMouseX = -1;
	int tempMouseY = -1;
	int tempIsMouseAt = false;

	int flags = 0;

	MyEngine* e;
	
	int clickable = false;
};

*/

#endif //_MYWIDGET_H