#include "Engine.h"

using namespace My;
using namespace std;

Engine My::engine;

#define THREAD_COUNT(...) mThreadCount.lock(); threadCount##__VA_ARGS__; mThreadCount.unlock();

Engine::Engine() {
	ZeroMemory(&d3dpp, sizeof(d3dpp));
}

void Engine::onInit(HINSTANCE hInstance) {
	g_hInstance = hInstance;

	initWnd();

	thread* thRender = new thread(&Engine::funcRender, this);
	thRender->detach();

	while (!getDirectxInited())
		Sleep(10);

	thread* thLogic = new thread(&Engine::funcLogic, this);
	thLogic->detach();
}

void Engine::initWnd() {
	//初始化窗口
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = g_hInstance;
	wc.lpfnWndProc = Engine::WndProc;
	wc.lpszClassName = TEXT("SurviveGameNewNew");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	g_hWnd = CreateWindow(wc.lpszClassName,
		TEXT("SurviveGameNewNew"), WS_OVERLAPPEDWINDOW, 40, 20,
		GetSystemMetrics(SM_CXFULLSCREEN) - 80, GetSystemMetrics(SM_CYFULLSCREEN) - 40,
		NULL, NULL, g_hInstance, NULL);

	//最大化
	ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);

	//得到画面宽高
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	int viewW = rect.right - rect.left;
	int viewH = rect.bottom - rect.top;
	setViewW(viewW);
	setViewH(viewH);
	setDefWidth(viewW);
	setDefHeight(viewH);
}

void Engine::initDirectx() {
	//创建D3D接口指针
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D显示模式结构体
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//获取当前显卡的显示模式
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//创建D3D的设备指针
	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = getDefWidth();
	d3dpp.BackBufferHeight = getDefHeight();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//翻转效果：抛弃

	//创建设备指针
	g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,		//默认显卡
		D3DDEVTYPE_HAL,			//硬件抽象层
		g_hWnd,					//所依附的窗口（要改造的窗口）
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//顶点软件处理模式
		&d3dpp,		//设备的能力
		&g_pDevice	//返回的设备指针
		);

	//创建精灵指针
	D3DXCreateSprite(g_pDevice, &g_pSprite);
	D3DXCreateSprite(g_pDevice, &g_pSpriteRender);

	#pragma region 销毁和恢复g_pRenderTexture的函数
	TextureManagerFunc releaseFunc = [](void* sendObj) {
		Engine* e = (Engine*)sendObj;
		safeRelease(e->g_pRenderTexture);
		safeRelease(e->g_pRenderSurface);
		safeRelease(e->g_pWindowSurface);
	};
	TextureManagerFunc resetFunc = [](void* sendObj) {
		Engine* e = (Engine*)sendObj;
		//"渲染到纹理"
		e->g_pDevice->CreateTexture(
			GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), 1,
			D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &e->g_pRenderTexture, NULL
			);
		//得到纹理的Surface
		e->g_pRenderTexture->GetSurfaceLevel(0, &e->g_pRenderSurface);

		//得到设备的Surface
		e->g_pDevice->GetRenderTarget(0, &e->g_pWindowSurface);
		e->g_pDevice->SetRenderTarget(0, e->g_pRenderSurface);
	};
	#pragma endregion
	renderTextureManager = new TextureManager(releaseFunc, resetFunc, this);
	TextureManager::addManager(renderTextureManager);

	//初始化字体
	D3DXCreateFont(g_pDevice, 20, 10, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFont);
	D3DXCreateFont(g_pDevice, 12, 6, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFontVerySmall);
	D3DXCreateFont(g_pDevice, 16, 8, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFontSmall);

	//初始化顶点
	g_pDevice->CreateVertexBuffer(4 * sizeof(Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
		D3DPOOL_MANAGED, &vbRectangle, nullptr);
	g_pDevice->CreateIndexBuffer(6 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &ibRectangle, 0);
	WORD* index = nullptr;
	ibRectangle->Lock(0, 0, (void**)&index, 0);
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 0;
	index[4] = 2;
	index[5] = 3;
	ibRectangle->Unlock();
}


void Engine::onDestroy() {
	setNeedExit(true);
	while (getThreadCount() == 0)
		Sleep(10);

	TextureManager::removeManager(renderTextureManager);
	safeDelete(renderTextureManager);
}


void Engine::funcLogic() {
	THREAD_COUNT(++);

	while (!getNeedExit()) {
		Sleep(10);
	}

	THREAD_COUNT(--);
}

void Engine::funcRender() {
	THREAD_COUNT(++);

	initDirectx();
	setDirectxInited(true);

	while (!getNeedExit()) {
		Sleep(10);
	}

	THREAD_COUNT(--);
}


LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE: {
		//setClosed(true);
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}