#include "utility.h"

HWND g_hWnd = 0;
HINSTANCE g_hInstance = 0;
/**
	需要释放的对象:
	g_pD3D , g_pDevice , g_pSprite , g_pSpriteRender
	data(g_pTexturePlayer , blocksTextureData(...))
	g_pRenderTexture , g_pRenderSurface
*/
LPDIRECT3D9 g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
LPDIRECT3DDEVICE9 g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
LPD3DXSPRITE g_pSprite = nullptr;		//D3D的精灵指针，为了画图
LPD3DXSPRITE g_pSpriteRender = nullptr;	//D3D的精灵指针，用来渲染到纹理



//游戏数据
#include "MyGame/MyReadGameData.h"
LPDIRECT3DTEXTURE9 g_pTexturePlayer = nullptr;	//玩家的贴图指针
MyBlocksTextureData blocksTextureData;	//方块贴图
MyData data;

// 渲染到纹理
BOOL isInit = false;
IDirect3DTexture9* g_pRenderTexture = NULL;
IDirect3DSurface9* g_pRenderSurface = NULL;

INT resizeTime = timeGetTime();	//上次大小被改变 的时间
INT doneTime = 0;	//完成初始化的时间

//耗时
//INT timeThreadLogic = 0;
//INT timeThreadRender = 0;

//画面大小
INT defWidth = 800;
INT defHeight = 608;

//屏幕大小
INT screenWidth = 0;
INT screenHeight = 0;

//按键状态
#include "MyGame/MyState.h"
BOOL hasFocus = true;
MyKey key;
MyMouse mouse;
MyVaribles vars;

//Room
#include "MyRooms/MyRoom_title.h"
#include "MyRooms/MyRoom_game.h"
MyRoom* currentRoom = nullptr;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);


VOID onInit() {
	//屏幕大小
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//创建D3D接口指针
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D显示模式结构体
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//获取当前显卡的显示模式
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//创建D3D的设备指针
	D3DPRESENT_PARAMETERS d3dpp;	//描述D3D设备的能力
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = defWidth;
	d3dpp.BackBufferHeight = defHeight;
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

	//"渲染到纹理"
	g_pDevice->CreateTexture(
		GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), 1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R5G6B5,
		D3DPOOL_DEFAULT,
		&g_pRenderTexture,
		NULL);
	//得到纹理的Surface
	g_pRenderTexture->GetSurfaceLevel(0, &g_pRenderSurface);

	//创建必要文件夹
	CreateDirectory(TEXT("data"), NULL);
	CreateDirectory(TEXT("data\\texture"), NULL);
	//读取游戏数据
	myCreateTexture(g_pDevice, "data\\texture\\player\\player.png", MyPlayer::plW, MyPlayer::plH, nullptr, &g_pTexturePlayer);	//读取玩家贴图
	blocksTextureData.onInit("data\\texture\\blocks", "blocks.info", g_pDevice);	//读取方块贴图

	//把指针传入vars，方便传递
	vars.g_pD3D = g_pD3D;
	vars.g_pDevice = g_pDevice;
	vars.g_pSprite = g_pSprite;
	vars.g_pSpriteRender = g_pSpriteRender;
	vars.g_pRenderTexture = g_pRenderTexture;
	vars.g_pRenderSurface = g_pRenderSurface;

	//把游戏数据指针传入data，方便传递
	data.g_pTexturePlayer = g_pTexturePlayer;	//玩家贴图
	data.origBlocksTextureData = &blocksTextureData;	//方块贴图

	//初始化Room
	setCurrentRoom(&currentRoom, new MyRoom_game(&key, &mouse, &vars, &data, 400, 400));
	//setCurrentRoom(&currentRoom, 
	//	new MyRoom_title(&key, &mouse, &vars, g_pD3D, g_pDevice, g_pSprite,
	//	g_pSpriteRender, g_pTexture, g_pRenderTexture, g_pRenderSurface)
	//);
	
}
INT onKeyAndMouseCheck() {
	//得到开始的时间
	int startTime = timeGetTime();
	//清空状态
	mouse.clearState();
	key.clearState();
	//设置状态
	if (hasFocus) {
		//键盘
		setState('W', &key.w, &key.w_pressed, &key.w_released);
		setState('A', &key.a, &key.a_pressed, &key.a_released);
		setState('S', &key.s, &key.s_pressed, &key.s_released);
		setState('D', &key.d, &key.d_pressed, &key.d_released);
		setState(VK_SPACE, &key.space, &key.space_pressed, &key.space_released);
		//鼠标
		setState(VK_LBUTTON, &mouse.left, &mouse.left_pressed, &mouse.left_released);
		setState(VK_MBUTTON, &mouse.mid, &mouse.mid_pressed, &mouse.mid_released);
		setState(VK_RBUTTON, &mouse.right, &mouse.right_pressed, &mouse.right_released);
		POINT m_mouse;
		GetCursorPos(&m_mouse);
		ScreenToClient(g_hWnd, &m_mouse);  //屏幕转化为客户端
		mouse.x = m_mouse.x;
		mouse.y = m_mouse.y;
	}
	//返回消耗的时间
	return timeGetTime() - startTime;
}

VOID onDestroy() {
	//Safe_Release(g_pFont);
	//Safe_Release(g_pTexture);
	Safe_Release(g_pRenderTexture);
	Safe_Release(g_pRenderSurface);
	Safe_Release(g_pSprite);
	Safe_Release(g_pSpriteRender);
	Safe_Release(g_pDevice);
	Safe_Release(g_pD3D);
}

VOID threadLoop(bool* flag) {
	while (true) {
		if (*flag) {
			*flag = false;
			break;
		}

		int currentTime = timeGetTime();
		onKeyAndMouseCheck();
		if (currentRoom) {
			currentRoom->onLogic();
			if (!IsIconic(g_hWnd)) {
				currentRoom->onRender();	//绘制
			}
		}
		//if (GetSystemMetrics(SM_CXSCREEN) != screenWidth || GetSystemMetrics(SM_CYSCREEN) != screenHeight) {
		//	cDebug("SHIT!!!!!!!!!\n");
		//}
		int elapsedTime = timeGetTime() - currentTime;
		if (elapsedTime < 16) {
			timeBeginPeriod(2);
			Sleep(16 - elapsedTime);
			timeEndPeriod(2);
		}
		

		
	}
}
//VOID threadRender(bool* flag) {
	//while (true) {
	//	if (*flag) {
	//		*flag = false;
	//		break;
	//	}
	//	int currentTime = timeGetTime();
	//	if (!IsIconic(g_hWnd) && currentTime - resizeTime > 120 ) {
	//		if (currentRoom)
	//			currentRoom->onRender();	//绘制
	//	}
	//	while (timeGetTime() - currentTime < 17)
	//		Sleep(1);
	//	timeThreadRender = currentTime;
	//}
//}

INT WINAPI WinMain(__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in_opt LPSTR lpCmdLine,
	__in int nShowCmd)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("SurviveGameNewNew");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	g_hWnd = CreateWindow(wc.lpszClassName,
		TEXT("SurviveGameNewNew"), WS_OVERLAPPEDWINDOW, 40, 20, 
		GetSystemMetrics(SM_CXFULLSCREEN) - 80, GetSystemMetrics(SM_CYFULLSCREEN) - 40, 
		NULL, NULL, hInstance, NULL);

	//最大化
	ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);

	//得到画面宽高
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	vars.viewW = rect.right - rect.left;
	vars.viewH = rect.bottom - rect.top;
	defWidth = vars.viewW;
	defHeight = vars.viewH;

	if (g_hWnd){
		g_hInstance = hInstance;

		onInit();
		isInit = true;

		UpdateWindow(g_hWnd);
	}

	//多线程
	bool flagLoop = false;
	std::thread thLoop(threadLoop, &flagLoop);
	thLoop.detach();

	//消息循环
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	doneTime = timeGetTime();
	while (true) {
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			flagLoop = true;
			while (flagLoop)
				Sleep(10);
			break;
		}
	}
	if (currentRoom) {
		currentRoom->onDestroy();
		Safe_Delete(currentRoom);
	}
	data.onDestroy();
	onDestroy();
	UnregisterClass(wc.lpszClassName, hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	//------焦点检测------
	case WM_KILLFOCUS:
		hasFocus = false;
		break;
	case WM_SETFOCUS:
		hasFocus = true;
		break;
	//------大小被改变----
	case WM_SIZE: {
		if (isInit) {
			resizeTime = timeGetTime();
			D3DXMATRIX g_scale;
			RECT rect;
			GetClientRect(g_hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			vars.viewW = w;
			vars.viewH = h;
			D3DXMatrixTransformation2D(
				&g_scale,		//返回的矩阵
				nullptr,		//缩放的中心
				0.0f,			//影响缩放的因素
				&D3DXVECTOR2((float)defWidth / w, (float)defHeight / h),	//在X、Y方向的缩放量
				nullptr,	//旋转中心
				0,			//旋转弧度
				nullptr		//平移量
			);
			g_pSpriteRender->SetTransform(&g_scale);
			D3DXMatrixIdentity(&g_scale);
		}
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE && timeGetTime() - doneTime > 10 )
			DestroyWindow(hWnd);
		break;
	case WM_CLOSE:
		if (timeGetTime() - doneTime > 10)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}