#pragma once

#include "utility.h"

#include "Class/TextureManager.h"
#include "Class/LimitSizeVector.h"

namespace My {
	class Engine;
}


class My::Engine {
public:
	explicit Engine();

	void onInit(HINSTANCE hInstance);
	void onDestroy();

	void onLogic();
	void onRenderStart();
	void onRenderEnd(int& err);

	std::mutex mutexGameLoop;
	void funcLogic();
	void funcRender();

	//绘制
	void drawRestart();
	void drawRect(int x, int y, int w, int h, DWORD col1 = 0xffffffff, DWORD col2 = 0xffffffff, DWORD col3 = 0xffffffff, DWORD col4 = 0xffffffff);
	void drawBorder(int x, int y, int w, int h, int size, DWORD col = 0xff000000);

	HRESULT resetDevice();

	LRESULT CALLBACK ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	//windows的一些东西
	HWND g_hWnd = 0;
	HINSTANCE g_hInstance = 0;
	//接口和设备指针
	D3DPRESENT_PARAMETERS d3dpp;	//描述D3D设备的能力
	LPDirectx g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
	LPDevice g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
	//渲染到纹理
	LPTexture g_pRenderTexture = nullptr;
	LPSurface g_pRenderSurface = nullptr;
	LPSurface g_pWindowSurface = nullptr;

	//精灵指针
	LPSprite g_pSprite = nullptr;		//D3D的精灵指针，为了画图
	LPSprite g_pSpriteRender = nullptr;	//D3D的精灵指针，用来渲染到纹理

	//字体
	LPD3DXFONT g_pFont = nullptr;
	LPD3DXFONT g_pFontSmall = nullptr;
	LPD3DXFONT g_pFontVerySmall = nullptr;

	//绘制矩形的顶点Buffer
	LPDIRECT3DVERTEXBUFFER9 vbRectangle = nullptr;
	LPDIRECT3DINDEXBUFFER9 ibRectangle = nullptr;

	//管理Texture
	TextureManager* renderTextureManager = nullptr;

	//清空时的颜色
	D3DCOLOR clearColor = D3DCOLOR_XRGB(102, 204, 255);


	std::mutex mThreadCount;
	NEEDLOCK_GET_FUNC(mThreadCount, ThreadCount, threadCount, int)

	NEEDLOCK_VARIBLE_FUNC(WndInited, wndInited, bool)
	NEEDLOCK_VARIBLE_FUNC(DirectxInited, directxInited, bool)

	NEEDLOCK_VARIBLE_FUNC(NeedExit, needExit, bool)
	NEEDLOCK_VARIBLE_FUNC(Closed, closed, bool)

	NEEDLOCK_VARIBLE_FUNC(ResizeTime, resizeTime, int)

	NEEDLOCK_VARIBLE_FUNC(LogicFps, logicFps, int)
	NEEDLOCK_VARIBLE_FUNC(RenderFps, renderFps, int)

	NEEDLOCK_VARIBLE_FUNC(DefWidth, defWidth, int)
	NEEDLOCK_VARIBLE_FUNC(DefHeight, defHeight, int)
	NEEDLOCK_VARIBLE_FUNC(ViewW, viewW, int)
	NEEDLOCK_VARIBLE_FUNC(ViewH, viewH, int)

private:
	void initWnd();
	void initDirectx();

	std::mutex mutexLogicRender;
#ifdef DEBUG_CONSOLE
	std::mutex mutexConsoleOutput;
#endif

	int threadCount = 0;

	bool wndInited = false, directxInited = false;
	bool needExit = false;
	bool closed = false;

	int resizeTime = 0;

	int logicFps = -1, renderFps = -1;

	int defWidth = 800, defHeight = 608;
	int viewW = 800, viewH = 608;

	LimitSizeVector<double> vecRenderPresentTime = LimitSizeVector<double>(20);
};

namespace My {
	extern Engine engine;
}