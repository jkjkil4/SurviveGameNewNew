#ifndef _MYENGINE_H
#define _MYENGINE_H

#include "utility.h"
#include "MyGame/MyData.h"
#include "MyNameSpace.h"
#include "MyClasses/MyExpr.h"
#include "MyGame/MyGlobal.h"

/*
	需要释放的对象：
	g_pD3D, g_pDevice, 
	g_pSprite, g_pSpriteRender,
	g_pRenderTexture, g_pRenderSurface, g_pWindowSurface,

	g_pFont

	vbRectangle
	ibRectangle
*/
class MyEngine
{
public:
	explicit MyEngine(void (*signalScaled)(), int* fps);

	void onInit();
	void renderStart();
	void renderEnd();
	void onDestroy();

	LRESULT ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//绘制
	void drawRestart();
	void drawRect(int x, int y, int w, int h, DWORD col1 = 0xffffffff, DWORD col2 = 0xffffffff, DWORD col3 = 0xffffffff, DWORD col4 = 0xffffffff);
	void drawBorder(int x, int y, int w, int h, int size, DWORD col1 = 0xff000000, DWORD col2 = 0xff000000, DWORD col3 = 0xff000000, DWORD col4 = 0xff000000);

	//------------------------------------------------------------------------------------//
	std::mutex m, changeRoomMutex;
	//全局变量
	MyGlobal global;
	//窗口、视野宽高
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
	//清空时的颜色
	D3DCOLOR clearColor = D3DCOLOR_XRGB(102, 204, 255);

	//一些东西
	int doneTime = 0, resizeTime = timeGetTime();
	bool isInited = false;
	bool hasFocus = true;
	void (*signalScaled)() = nullptr;

	//按键检测
	bool keyFlag(int num);
	void setKeyFlag(int num, bool flag);
	bool keyPressFlag(int num);
	void setKeyPressFlag(int num, bool flag);
	bool keyReleaseFlag(int num);
	void setKeyReleaseFlag(int num, bool flag);
	std::vector<MyKey*> vec_keyBuffer;
	static constexpr int keyNumber = 0x88;
	bool key[keyNumber];
	bool keyPressed[keyNumber];
	bool keyReleased[keyNumber];
	int mice[3]{ VK_LBUTTON, VK_MBUTTON, VK_RBUTTON };

	//滚轮delta
	int wheelDelta = 0;

	//鼠标位置
	int mouseX = -1;
	int mouseY = -1;

	//输入的字符
	std::wstring inputWString = TEXT("");

	//字体
	LPD3DXFONT g_pFont = nullptr;
	LPD3DXFONT g_pFontSmall = nullptr;
	LPD3DXFONT g_pFontVerySmall = nullptr;

	//绘制矩形的顶点Buffer
	LPDIRECT3DVERTEXBUFFER9 vbRectangle;
	LPDIRECT3DINDEXBUFFER9 ibRectangle;

	//pointer
	int* fps = nullptr;
};


#endif //_MYENGINE_H