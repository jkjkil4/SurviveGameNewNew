#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"

class MyRoom
{
public:
	explicit MyRoom(MyKey key, MyMouse mouse, LPDIRECT3D9 g_pD3D, LPDIRECT3DDEVICE9 g_pDevice,
		LPD3DXSPRITE g_pSprite, LPD3DXSPRITE g_pSpriteRender, LPDIRECT3DTEXTURE9 g_pTexture,
		IDirect3DTexture9* g_pRenderTexture, IDirect3DSurface9* g_pRenderSurface);
	virtual int onLogic() { return 0; }
	virtual int onRender() { return 0; }
	virtual void onDestroy(){}

	LPDIRECT3D9 g_pD3D = nullptr;				//D3D的接口指针
	LPDIRECT3DDEVICE9 g_pDevice = nullptr;		//D3D的设备指针
	LPD3DXSPRITE g_pSprite = nullptr;			//D3D的精灵指针，为了画图
	LPD3DXSPRITE g_pSpriteRender = nullptr;		//D3D的精灵指针，用来渲染到纹理
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;	//纹理对象

	IDirect3DTexture9* g_pRenderTexture = NULL;
	IDirect3DSurface9* g_pRenderSurface = NULL;
};