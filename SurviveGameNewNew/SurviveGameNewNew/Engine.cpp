#include "Engine.h"

#include "Class/Delayer.h"

using namespace My;
using namespace std;

Engine My::engine;

#define NoError 0
#define ErrorCannotPresent 1

#define THREAD_COUNT(...) mThreadCount.lock(); threadCount##__VA_ARGS__; mThreadCount.unlock();
#define DELAY_MICRO (1000000 / 60)

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

	setWndInited(true);
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
	renderTextureManager->resetTexture();
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

	safeRelease(vbRectangle);
	safeRelease(ibRectangle);

	safeRelease(g_pFontVerySmall);
	safeRelease(g_pFontSmall);
	safeRelease(g_pFont);

	safeRelease(g_pSprite);
	safeRelease(g_pSpriteRender);

	safeRelease(g_pRenderTexture);
	safeRelease(g_pRenderSurface);
	safeRelease(g_pWindowSurface);

	safeRelease(g_pDevice);
	safeRelease(g_pD3D);
}


void Engine::funcLogic() {
	THREAD_COUNT(++);

	timeBeginPeriod(1);
	Counter counter;
	counter.start();
	Delayer delayer(DELAY_MICRO);
	int fpsCount = 0;
	double fpsStartTime = counter.getTime();

	while (!getNeedExit()) {
		double startTime = counter.getTime();
		mutexLogicRender.lock();
		onLogic();
		mutexLogicRender.unlock();
		int spentMicro = (int)((counter.getTime() - startTime) * 1000);
		delayer.delay(DELAY_MICRO - spentMicro);

		fpsCount++;
		double time = counter.getTime();
		if (time - fpsStartTime > 1000) {
			setLogicFps(fpsCount);

			#ifdef DEBUG_CONSOLE
			mutexConsoleOutput.lock();
			SetConsoleAtt(FORE_YELLOW);
			cout << "Logic\t FPS: " << fpsCount << "\tDebug: " << time << "\t " << (long long)(time * 1000) << "\t  " << (int)((time - startTime) * 1000) << endl;
			SetConsoleAtt(FORE_WHITE);
			mutexConsoleOutput.unlock();
			#endif

			fpsCount = 0;
			fpsStartTime = time;
		}
	}
	timeEndPeriod(1);

	THREAD_COUNT(--);
}

void Engine::funcRender() {
	THREAD_COUNT(++);

	initDirectx();
	setDirectxInited(true);

	timeBeginPeriod(1);
	Counter counter;
	counter.start();
	Delayer delayer(DELAY_MICRO);
	int fpsCount = 0;
	double fpsStartTime = counter.getTime();

	while (!getNeedExit()) {
		double startTime = counter.getTime();
		int err = NoError;
		if (!IsIconic(g_hWnd)) {
			onRenderStart();
			mutexLogicRender.lock();

			//TODO: 绘制
			drawRect(50, 50, 200, 100, 0xff00ffff, 0xffff00ff, 0xff00ff00, 0xffff0000);
			wstring debugWString = _T("LogicFps: ") + to_wstring(getLogicFps()) + _T("   RenderFps: ") + to_wstring(getRenderFps());
			g_pFont->DrawText(g_pSprite, debugWString.c_str(), -1, nullptr, DT_LEFT | DT_TOP, 0xff000000);

			g_pFontSmall->DrawText(g_pSprite, _T("这是g_pDevice->Present()的耗时"), -1, &mkRect(0, 60, 250, 20), DT_LEFT, 0xff000000);
			int i = 0;
			for (auto it = vecRenderPresentTime.begin(); it < vecRenderPresentTime.end(); it++) {
				g_pFontSmall->DrawText(g_pSprite, (to_wstring(*it)).c_str(), -1, &mkRect(0, 80 + 20 * i, 100, 20), DT_LEFT, 0xff000000);
				i++;
			}

			mutexLogicRender.unlock();
			onRenderEnd(err);
			
			if (err == ErrorCannotPresent) {
				resetDevice();
			}
		}
		int spentMicro = (err == NoError) ? (int)((counter.getTime() - startTime) * 1000) : 0;
		delayer.delay(DELAY_MICRO - spentMicro, true);

		fpsCount++;
		double time = counter.getTime();
		if (time - fpsStartTime > 1000) {
			setRenderFps(fpsCount);

			#ifdef DEBUG_CONSOLE
			mutexConsoleOutput.lock();
			SetConsoleAtt(FORE_PINK);
			cout << "Render\t FPS: " << fpsCount << endl;
			SetConsoleAtt(FORE_WHITE);
			mutexConsoleOutput.unlock();
			#endif

			fpsCount = 0;
			fpsStartTime = time;
		}
	}
	timeEndPeriod(1);

	THREAD_COUNT(--);
}


void Engine::onLogic() {

}

void Engine::onRenderStart() {
	//填充
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, clearColor, 1.0f, 0);
	//开始绘制
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Engine::onRenderEnd(int& err) {
	//结束绘制
	g_pSprite->End();
	//将纹理绘制到窗口
	g_pDevice->SetRenderTarget(0, g_pWindowSurface);	//设置为绘制到窗口
	g_pDevice->BeginScene();	//获取绘制权限
	g_pSpriteRender->Begin(0);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//结束绘制
	
	Counter counter;
	counter.start();
	HRESULT hr = g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	vecRenderPresentTime.addElement(counter.getTime());

	if (FAILED(hr) && !getClosed())
		err = ErrorCannotPresent;

	g_pDevice->SetRenderTarget(0, g_pRenderSurface);	//设置为绘制到g_pRenderSurface
	
}


void Engine::drawRestart() {
	g_pSprite->End();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Engine::drawRect(int x, int y, int w, int h, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
	Vertex* vertexs;
	vbRectangle->Lock(0, 0, (void**)&vertexs, 0);
	vertexs[0] = Vertex{ (float)x, (float)y, 0.0f, 1.0f, col1 };
	vertexs[1] = Vertex{ (float)(x + w), (float)y, 0.0f, 1.0f, col2 };
	vertexs[2] = Vertex{ (float)(x + w), (float)(y + h), 0.0f, 1.0f, col3 };
	vertexs[3] = Vertex{ (float)x, (float)(y + h), 0.0f, 1.0f, col4 };
	vbRectangle->Unlock();

	g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	g_pDevice->SetStreamSource(0, vbRectangle, 0, sizeof(Vertex));
	g_pDevice->SetIndices(ibRectangle);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Engine::drawBorder(int x, int y, int w, int h, int size, DWORD col) {
	//左侧
	drawRect(x, y, size, h, col, col, col, col);
	//右侧
	drawRect(x + w - size, y, size, h, col, col, col, col);
	//顶部
	drawRect(x + size, y, w - 2 * size, size, col, col, col, col);
	//底部
	drawRect(x + size, y + h - size, w - 2 * size, size, col, col, col, col);
}

HRESULT Engine::resetDevice() {
	Sleep(100);
	int startTime = timeGetTime();
	//检查设备状态
	HRESULT hr = g_pDevice->TestCooperativeLevel();

	//设备能被Reset
	if (hr == D3DERR_DEVICENOTRESET) {
		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
		cout << "Is Reseting Device" << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif

		g_pSprite->OnLostDevice();
		g_pSpriteRender->OnLostDevice();
		g_pFont->OnLostDevice();
		g_pFontSmall->OnLostDevice();
		g_pFontVerySmall->OnLostDevice();
		TextureManager::onReleaseTextures();

	retry:
		//Reset设备
		HRESULT hr2;
		int times = 0;
		for (int i = 0; i < 10; i++) {
			hr2 = g_pDevice->Reset(&d3dpp);
			times++;
			if (SUCCEEDED(hr2))
				break;
		}
		if (SUCCEEDED(hr2)) {
			g_pSprite->OnResetDevice();
			g_pSpriteRender->OnResetDevice();
			g_pFont->OnResetDevice();
			g_pFontSmall->OnResetDevice();
			g_pFontVerySmall->OnResetDevice();
			TextureManager::onResetTextures();

			#ifdef DEBUG_CONSOLE
			SetConsoleAtt(FORE_GREEN + FORE_LIGHT);
			cout << "Reset Device 成功\t  本次尝试次数(最大10):" << times << "\t  本次消耗时间(ms):" << timeGetTime() - startTime << endl;
			SetConsoleAtt(FORE_WHITE);
			#endif
		}
		else {
			//Reset设备失败
			#ifdef DEBUG_CONSOLE
			SetConsoleAtt(FORE_RED + FORE_LIGHT);
			cout << "Reset Device 失败\t" << hr2 << endl;
			SetConsoleAtt(FORE_WHITE);
			#endif

			int res = MessageBox(nullptr, TEXT("重置设备失败\n\n重试? (取消则会退出)"), TEXT("错误"), MB_OKCANCEL);
			if (res == 1) {
				goto retry;
			}
			else {
				SendMessage(g_hWnd, WM_CLOSE, 0, 0);
			}
		}
	}
	else if (hr == D3DERR_DEVICELOST) {
		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_RED + FORE_LIGHT);
		cout << "Device Lost" << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif

		Sleep(25);
	}

	return hr;
}


LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return engine.ProcWndMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Engine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_SIZE: {//大小被改变
		if (getWndInited()) {
			//setResizeTime(timeGetTime());
			D3DXMATRIX g_scale;
			RECT rect;
			GetClientRect(g_hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			setViewW(w);
			setViewH(h);
			setSpriteScale(g_pSpriteRender, 0, 0, (float)getDefWidth() / w, (float)getDefHeight() / h);
			//TODO: 调整控件的位置
		}
		break;
	}
	case WM_CLOSE: {
		setClosed(true);
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