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

	LPDIRECT3D9 g_pD3D = nullptr;				//D3D�Ľӿ�ָ��
	LPDIRECT3DDEVICE9 g_pDevice = nullptr;		//D3D���豸ָ��
	LPD3DXSPRITE g_pSprite = nullptr;			//D3D�ľ���ָ�룬Ϊ�˻�ͼ
	LPD3DXSPRITE g_pSpriteRender = nullptr;		//D3D�ľ���ָ�룬������Ⱦ������
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;	//�������

	IDirect3DTexture9* g_pRenderTexture = NULL;
	IDirect3DSurface9* g_pRenderSurface = NULL;
};