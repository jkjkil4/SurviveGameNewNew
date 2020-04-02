#ifndef _MYENGINE_H
#define _MYENGINE_H

#include "utility.h"
#include "MyGame/MyData.h"
/*
	需要释放的对象：
	g_pD3D, g_pDevice, 
	g_pSprite, g_pSpriteRender,
	g_pRenderTexture, g_pRenderSurface, g_pWindowSurface
*/
class MyEngine
{
private:
	struct MyKey {
		bool flag;
		int key;
	};

public:
	explicit MyEngine(int* fps);

	void onInit();
	void renderStart();
	void renderEnd();
	void onDestroy();

	LRESULT ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//------------------------------------------------------------------------------------//
	int defWidth = 800, defHeight = 608;
	int viewW = 800, viewH = 608;
	//windows的一些东西
	HWND g_hWnd = 0;
	HINSTANCE g_hInstance = 0;
	//接口和设备指针
	LPDIRECT3D9 g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
	LPDIRECT3DDEVICE9 g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
	//精灵指针
	LPD3DXSPRITE g_pSprite = nullptr;		//D3D的精灵指针，为了画图
	LPD3DXSPRITE g_pSpriteRender = nullptr;	//D3D的精灵指针，用来渲染到纹理
	// 渲染到纹理
	IDirect3DTexture9* g_pRenderTexture = nullptr;
	IDirect3DSurface9* g_pRenderSurface = nullptr;
	IDirect3DSurface9* g_pWindowSurface = nullptr;
	//处理
	void onKeyCheck();
	//贴图
	MyData data;
	//一些东西
	int doneTime = 0, resizeTime = timeGetTime();
	bool isInited = false;
	bool hasFocus = true;
	//按键检测
	bool keyFlag(int num);
	void setKeyFlag(int num, bool flag);
	bool keyPressFlag(int num);
	void setKeyPressFlag(int num, bool flag);
	bool keyReleaseFlag(int num);
	void setKeyReleaseFlag(int num, bool flag);
	std::vector<MyKey*> vec_keyBuffer;
	bool key[123];
	bool keyPressed[123];
	bool keyReleased[123];
	//鼠标位置
	int mouseX = -1;
	int mouseY = -1;

	//pointer
	int* fps = nullptr;
};


#endif //_MYENGINE_H