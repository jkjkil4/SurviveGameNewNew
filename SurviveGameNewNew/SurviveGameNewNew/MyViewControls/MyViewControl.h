#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"

#define AlignFlag_left		1
#define AlignFlag_right		2
#define AlignFlag_top		4
#define AlignFlag_bottom	8

class MyViewControl
{
public:
	explicit MyViewControl(MyKey* key, MyMouse* mouse, MyVaribles* vars, LPDIRECT3DTEXTURE9 g_pTexture) {
		this->key = key;
		this->mouse = mouse;
		this->vars = vars;
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
				rectLeft = vars->viewW - x - w;
			}
			else {
				rectLeft = (vars->viewW - w) / 2 + x;
			}
			mouseX -= rectLeft;

			int rectTop;
			if (top) {
				rectTop = y;
			}
			else if (bottom) {
				rectTop = vars->viewH - y - h;
			}
			else {
				rectTop = (vars->viewH - h) / 2 + y;
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
			posX = vars->viewW - x - w;
		} else {
			posX = (vars->viewW - w) / 2 + x;
		}

		if (top) {
			posY = y;
		} else if (bottom) {
			posY = vars->viewH - y - h;
		} else {
			posY = (vars->viewH - h) / 2 + y;
		}

		if (clickable) {
			if (checkMouseAt(mouse->x, mouse->y)) {
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

	MyKey* key;
	MyMouse* mouse;
	MyVaribles* vars;
	
	int clickable = false;
};