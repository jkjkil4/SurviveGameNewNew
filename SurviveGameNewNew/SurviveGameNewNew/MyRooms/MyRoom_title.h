#pragma once
#include "MyRoom.h"

class MyRoom_title : public MyRoom
{
public:
	MyRoom_title(MyKey* key, MyMouse* mouse, MyVaribles* vars, LPDIRECT3D9 g_pD3D, LPDIRECT3DDEVICE9 g_pDevice,
		LPD3DXSPRITE g_pSprite, LPD3DXSPRITE g_pSpriteRender, LPDIRECT3DTEXTURE9 g_pTexture,
		IDirect3DTexture9* g_pRenderTexture, IDirect3DSurface9* g_pRenderSurface)
	: MyRoom(key, mouse, vars, g_pD3D, g_pDevice, g_pSprite, g_pSpriteRender, g_pTexture, g_pRenderTexture, g_pRenderSurface)
	{
		onInit();
	}

	void onInit();
	int onLogic() override;
	int onRender() override;
	void onDestroy() override;

	INT t = 0;

	LPD3DXFONT g_pFont = nullptr;	//×ÖÌå¶ÔÏó
};

