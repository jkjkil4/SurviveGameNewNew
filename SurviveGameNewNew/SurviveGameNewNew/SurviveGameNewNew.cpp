#include "utility.h"
#include <cmath>

#include <iostream>
#include <sstream>
#include <fstream>

#define PI acos(-1)

HWND g_hWnd = 0;
HINSTANCE g_hInstance = 0;

/*
绘图窗口改造的步骤：
1、包含头文件及库文件，见Utility.h文件
2、声明变量
3、创建D3D接口指针
4、创建D3D设备指针
5、创建Sprite精灵指针
6、改造onRender函数
*/

//COM：组件对象模型

LPDIRECT3D9 g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
LPDIRECT3DDEVICE9 g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
LPD3DXSPRITE g_pSprite = nullptr;		//D3D的精灵指针，为了画图
LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
INT t = 0;

INT timeLogic = 0;	//逻辑时间
INT timeDraw = 10;	//绘制时间
//INT wBefore = -1;
//INT hBefore = -1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

VOID onInit()
{
	//3、创建D3D接口指针
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D显示模式结构体
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//获取当前显卡的显示模式
	g_pD3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,		//哪张显卡的显示模式
		&d3ddm);				//获取到的显示模式的存储位置

	//4、创建D3D的设备指针
	D3DPRESENT_PARAMETERS d3dpp;	//描述D3D设备的能力
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;	//后台缓冲区的个数（双缓冲技术）

	//-----窗口模式的写发-----
	d3dpp.Windowed = TRUE;		//当前窗口是否为"窗口模式"

	//-----全屏模式的写发-----
	//d3dpp.Windowed = FALSE;
	//d3dpp.BackBufferWidth = d3ddm.Width;
	//d3dpp.BackBufferHeight = d3ddm.Height;

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


	//5、创建精灵指针
	D3DXCreateSprite(
		g_pDevice,		//设备指针
		&g_pSprite);	//返回的精灵指针

	D3DXIMAGE_INFO imageInfo;
	myCreateTexture( g_pDevice, "texture\\test.png",
		             &imageInfo, &g_pTexture );

}
VOID onLogic(float fElapsedTime)
{
	//得到逻辑开始时的时间
	long long tStart = getCurrentTime();
	//RECT rect;
	//GetClientRect(g_hWnd, &rect);
	//int w = rect.right - rect.left;
	//int h = rect.bottom - rect.top;
	//if (w != wBefore || h != hBefore) {
	//	wBefore = w;
	//	hBefore = h;

	//}
	t++;
	//得到逻辑消耗的时间
	timeLogic = static_cast<int>(getCurrentTime() - tStart);
}
VOID onRender(float fElapsedTime)
{
	//得到绘制开始时的时间
	long long tStart = getCurrentTime();
	g_pDevice->Clear(
		0,			//清空矩形的数量
		nullptr,	//清空矩形的临接信息
		D3DCLEAR_TARGET,	//要清空颜色缓冲区
		D3DCOLOR_XRGB(102, 204, 255),	//清成什么颜色   由于我喜欢洛天依，我每次都清成天依蓝
		1.0f,	//深度缓冲区的初始值
		0		//模板缓冲区的初始值
	);
	g_pDevice->BeginScene();		//获取绘制权限
	//---------------------------------------
	//		渲染代码
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);//参数告知系统，需要alpha混合的支持
	//Sprite的绘制函数
	g_pSprite->Draw(
		g_pTexture,				//绘制哪张图片		
		nullptr,	//绘制图片的哪个部分
		&D3DXVECTOR3(0, 0, 0),	//图片的锚点
		&D3DXVECTOR3(0, 0, 0),	//绘制在客户区的哪个位置
		D3DCOLOR_XRGB((int)(cos(t * PI / 180) * 127 + 127), (int)(sin(t * PI / 180) * 127 + 127), 255)//绘制混合色
	);
	g_pSprite->End();	//告诉系统，在3D的窗口中绘制2D的工作结束
	//---------------------------------------
	g_pDevice->EndScene();		//结束绘制
	//前后台缓冲区交换的"源动力"
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);
	//得到绘制消耗的时间
	timeDraw = static_cast<int>(getCurrentTime() - tStart);
}
VOID onDestroy()
{
	Safe_Release(g_pTexture);
	Safe_Release(g_pSprite);
	Safe_Release(g_pDevice);
	Safe_Release(g_pD3D);
}

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
		TEXT("Linimass"), WS_OVERLAPPEDWINDOW,
		50, 20, 800, 600, NULL, NULL, hInstance, NULL);

	if (g_hWnd)
	{
		g_hInstance = hInstance;

		onInit();

		ShowWindow(g_hWnd, SW_SHOWNORMAL);
		UpdateWindow(g_hWnd);
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		static DWORD dwTime = timeGetTime();
		DWORD dwCurrentTime = timeGetTime();
		DWORD dwElapsedTime = dwCurrentTime - dwTime;
		float fElapsedTime = dwElapsedTime * 0.001f;
		onLogic(fElapsedTime);	//逻辑
		if (!IsIconic(g_hWnd)) {
			onRender(fElapsedTime);	//绘制
		}
		if (dwElapsedTime < 1000 / 120)
			Sleep(1000 / 120 - dwElapsedTime);	//延时
		dwTime = dwCurrentTime;
	}
	onDestroy();
	UnregisterClass(wc.lpszClassName, hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}