#include "utility.h"
#include <cmath>

#include <iostream>
#include <sstream>
#include <fstream>

#define PI acos(-1)

HWND g_hWnd = 0;
HINSTANCE g_hInstance = 0;


LPDIRECT3D9 g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
LPDIRECT3DDEVICE9 g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
LPD3DXSPRITE g_pSprite = nullptr;		//D3D的精灵指针，为了画图
LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
INT t = 0;
INT currentT = 0;

INT timeThreadLogic = 0;	//逻辑处理
INT timeThreadRender = 0;	//渲染



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

VOID onInit() {
	//创建D3D接口指针
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D显示模式结构体
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//获取当前显卡的显示模式
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//创建D3D的设备指针
	D3DPRESENT_PARAMETERS d3dpp;	//描述D3D设备的能力
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;	//后台缓冲区的个数（双缓冲技术）
	d3dpp.Windowed = TRUE;
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

	D3DXIMAGE_INFO imageInfo;
	myCreateTexture( g_pDevice, "texture\\test2.png", &imageInfo, &g_pTexture );
}
INT onLogic() {
	//得到逻辑处理开始时的时间
	int tStart = timeGetTime();
	//逻辑处理
	t++;
	//得到逻辑处理消耗的时间
	return timeGetTime() - tStart;
}
INT onRender() {
	//得到绘制开始时的时间
	int tStart = timeGetTime();
	//D3DCOLOR_XRGB(102, 204, 255)
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	g_pDevice->BeginScene();		//获取绘制权限
	//---------------------------------------
	//		渲染代码
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);//参数告知系统，需要alpha混合的支持
	//Sprite的绘制函数
	g_pSprite->Draw(
		g_pTexture,				//绘制哪张图片		
		nullptr,	//绘制图片的哪个部分
		&D3DXVECTOR3(0, 0, 0),	//图片的锚点
		&D3DXVECTOR3(t/5.0f, 0, 0),	//绘制在客户区的哪个位置
		D3DCOLOR_XRGB((int)(cos(t * PI / 180) * 127 + 127), (int)(sin(t * PI / 180) * 127 + 127), 255)//绘制混合色
	);
	g_pSprite->End();	//告诉系统，在3D的窗口中绘制2D的工作结束
	//---------------------------------------
	g_pDevice->EndScene();		//结束绘制
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	return timeGetTime() - tStart;	//得到绘制消耗的时间
}
VOID onDestroy() {
	Safe_Release(g_pTexture);
	Safe_Release(g_pSprite);
	Safe_Release(g_pDevice);
	Safe_Release(g_pD3D);
}

VOID threadLogic(bool* flag) {
	while (true) {
		if (*flag)
			break;
		onLogic();
		Sleep(17);
	}
}
VOID threadRender(bool* flag) {
	while (true) {
		if (*flag)
			break;
		int currentTime = timeGetTime();
		int elapsedTime = currentTime - timeThreadRender;
		if (!IsIconic(g_hWnd)) {
			onRender();	//绘制
		}
		if (elapsedTime < 17)
			Sleep(17 - elapsedTime);	//延时
		timeThreadRender = currentTime;
	}
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

	if (g_hWnd){
		g_hInstance = hInstance;

		onInit();

		ShowWindow(g_hWnd, SW_SHOWNORMAL);
		UpdateWindow(g_hWnd);
	}

	//多线程
	bool flagLogic = false;
	std::thread thLogic(threadLogic, &flagLogic);
	thLogic.detach();
	bool flagRender = false;
	std::thread thRender(threadRender, &flagRender);
	thRender.detach();

	//消息循环
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (true) {
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			flagLogic = true;
			flagRender = true;
			break;
		}
	}
	onDestroy();
	UnregisterClass(wc.lpszClassName, hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
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