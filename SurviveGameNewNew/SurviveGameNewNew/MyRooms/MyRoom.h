#pragma once

#include "../utility.h"
#include "../MyGame/MyState.h"

class MyRoom
{
public:
	explicit MyRoom(MyKey* key, MyMouse* mouse, MyVaribles* vars, LPDIRECT3D9 g_pD3D, LPDIRECT3DDEVICE9 g_pDevice,
		LPD3DXSPRITE g_pSprite, LPD3DXSPRITE g_pSpriteRender, LPDIRECT3DTEXTURE9 g_pTexture,
		IDirect3DTexture9* g_pRenderTexture, IDirect3DSurface9* g_pRenderSurface) {
		this->key = key;
		this->mouse = mouse;
		this->vars = vars;
		this->g_pD3D = g_pD3D;
		this->g_pDevice = g_pDevice;
		this->g_pSprite = g_pSprite;
		this->g_pSpriteRender = g_pSpriteRender;
		this->g_pTexture = g_pTexture;
		this->g_pRenderTexture = g_pRenderTexture;
		this->g_pRenderSurface = g_pRenderSurface;
	}
	void setCurrentRoom(MyRoom** currentRoom) {
		this->currentRoom = currentRoom;
	}
	virtual int onLogic() { return 0; }
	virtual int onRender() { return 0; }
	virtual void onDestroy(){}

	MyRoom** currentRoom = nullptr;

	MyKey* key;
	MyMouse* mouse;
	MyVaribles* vars;

	LPDIRECT3D9 g_pD3D = nullptr;				//D3D的接口指针
	LPDIRECT3DDEVICE9 g_pDevice = nullptr;		//D3D的设备指针
	LPD3DXSPRITE g_pSprite = nullptr;			//D3D的精灵指针，为了画图
	LPD3DXSPRITE g_pSpriteRender = nullptr;		//D3D的精灵指针，用来渲染到纹理
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;	//纹理对象

	IDirect3DTexture9* g_pRenderTexture = NULL;
	IDirect3DSurface9* g_pRenderSurface = NULL;
};

static void setCurrentRoom(MyRoom** currentRoom, MyRoom* room) {
	if (*currentRoom) {
		(*currentRoom)->onDestroy();
		Safe_Delete(*currentRoom);
	}
	*currentRoom = room;
	room->setCurrentRoom(currentRoom);
}