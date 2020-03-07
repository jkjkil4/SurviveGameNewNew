#include "MyRoom.h"

MyRoom::MyRoom(MyKey* key, MyMouse* mouse, LPDIRECT3D9 g_pD3D, LPDIRECT3DDEVICE9 g_pDevice, LPD3DXSPRITE g_pSprite, LPD3DXSPRITE g_pSpriteRender, LPDIRECT3DTEXTURE9 g_pTexture, IDirect3DTexture9* g_pRenderTexture, IDirect3DSurface9* g_pRenderSurface)
{
	this->key = key;
	this->mouse = mouse;
	this->g_pD3D = g_pD3D;
	this->g_pDevice = g_pDevice;
	this->g_pSprite = g_pSprite;
	this->g_pSpriteRender = g_pSpriteRender;
	this->g_pTexture = g_pTexture;
	this->g_pRenderTexture = g_pRenderTexture;
	this->g_pRenderSurface = g_pRenderSurface;
	//onInit();
}

void MyRoom::setCurrentRoom(MyRoom** currentRoom){
	this->currentRoom = currentRoom;
}
