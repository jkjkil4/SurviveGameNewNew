#include "MyEngine.h"

using namespace std;

MyEngine::MyEngine(void (*signalScaled)(), bool (*canClose)(), void (*onLostDevice)(), void (*onResetDevice)(), int* fps)
	: signalScaled(signalScaled), canClose(canClose), onLostDevice(onLostDevice), onResetDevice(onResetDevice), fps(fps)
{
	ZeroMemory(keyPressed, sizeof(bool) * keyNumber);
	ZeroMemory(keyReleased, sizeof(bool) * keyNumber);
	ZeroMemory(key, sizeof(bool) * keyNumber);
}

void MyEngine::onInit() {
	//创建D3D接口指针
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D显示模式结构体
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//获取当前显卡的显示模式
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//创建D3D的设备指针
	ZeroMemory(&d3dpp, sizeof(d3dpp));
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
	
	//渲染到纹理
	createRenderTarget();

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

	//其他操作
	data.onInit("data\\texture", g_pDevice);
	setDoneTime(timeGetTime());
}
void MyEngine::onKeyCheck() {
	//键盘按键和鼠标按键
	ZeroMemory(keyPressed, sizeof(bool) * keyNumber);
	ZeroMemory(keyReleased, sizeof(bool) * keyNumber);
	for (auto it = vec_keyBuffer.begin(); it < vec_keyBuffer.end(); it++) {
		MyKey* key = *it;
		if (!key->isForWidget)
			key->flag ? setKeyPressFlag(key->key, true) : setKeyReleaseFlag(key->key, true);
		safeDelete(key);

	}
	vec_keyBuffer.clear();
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(g_hWnd, &mPos);
	mouseX = mPos.x;
	mouseY = mPos.y;
}
void MyEngine::renderStart() {
	//填充
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, clearColor, 1.0f, 0);
	//开始绘制
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void MyEngine::renderEnd() {
	//结束绘制
	g_pSprite->End();
	//将纹理绘制到窗口
	g_pDevice->SetRenderTarget(0, g_pWindowSurface);	//设置为绘制到窗口
	g_pDevice->BeginScene();	//获取绘制权限
	g_pSpriteRender->Begin(0);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//结束绘制

	HRESULT hr = g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	if (FAILED(hr))
		resetDevice();

	g_pDevice->SetRenderTarget(0, g_pRenderSurface);	//设置为绘制到g_pRenderSurface
}
void MyEngine::onDestroy() {
	//释放
	safeRelease(g_pD3D);
	safeRelease(g_pDevice);
	safeRelease(g_pSprite);
	safeRelease(g_pSpriteRender);
	safeRelease(g_pRenderTexture);
	safeRelease(g_pRenderSurface);
	safeRelease(g_pWindowSurface);

	safeRelease(g_pFont);

	safeRelease(vbRectangle);
	safeRelease(ibRectangle);

	//销毁
	for (auto it = vec_keyBuffer.begin(); it < vec_keyBuffer.end(); it++)
		delete(*it);
	vec_keyBuffer.clear();

	//destroy
	data.onDestroy();
}

void MyEngine::createRenderTarget() {
	//"渲染到纹理"
	g_pDevice->CreateTexture(
		GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &g_pRenderTexture, NULL
		);
	//得到纹理的Surface
	g_pRenderTexture->GetSurfaceLevel(0, &g_pRenderSurface);
	
	//得到设备的Surface
	g_pDevice->GetRenderTarget(0, &g_pWindowSurface);
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);
}
HRESULT MyEngine::resetDevice() {
	int startTime = timeGetTime();
	//检查设备状态
	HRESULT hr = g_pDevice->TestCooperativeLevel();

	//设备能被Reset
	if (SUCCEEDED(hr) || hr == D3DERR_DEVICENOTRESET) {
		g_pSprite->OnLostDevice();
		g_pSpriteRender->OnLostDevice();
		g_pFont->OnLostDevice();
		g_pFontSmall->OnLostDevice();
		g_pFontVerySmall->OnLostDevice();
		safeRelease(g_pRenderTexture);
		safeRelease(g_pRenderSurface);
		safeRelease(g_pWindowSurface);
		onLostDevice();
		
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
			createRenderTarget();
			onResetDevice();
			myd("Reset成功\t  本次尝试次数(最大10):" << times << "\t  本次消耗时间(ms):" << timeGetTime() - startTime << endl);
		}
		else {
			//Reset设备失败
			myd("Reset失败\t" << hr2 << endl);
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
		Sleep(25);
	}
	else {	
		//其他错误
		MessageBox(nullptr, TEXT("重置设备失败1"), TEXT("错误"), MB_OK);
	}

	return hr;
}

LRESULT MyEngine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
		//------焦点检测------
	case WM_KILLFOCUS: {
		setHasFocus(false);
		break;
	}
	case WM_SETFOCUS: {
		setHasFocus(true);
		break;
	}
		//------大小被改变----
	case WM_SIZE: {
		if (getInited()) {
			setResizeTime(timeGetTime());
			D3DXMATRIX g_scale;
			RECT rect;
			GetClientRect(g_hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			setViewW(w);
			setViewH(h);
			mySetScale(g_pSpriteRender, 0, 0, (float)getDefWidth() / w, (float)getDefHeight() / h);
			signalScaled();
		}
		break;
	}
	case WM_LBUTTONDOWN: {	//1
		setKeyFlag(1, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 1 });
		break;
	}
	case WM_LBUTTONUP: {
		setKeyFlag(1, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 1 });
		break;
	}
	case WM_MBUTTONDOWN: {	//4
		setKeyFlag(4, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 4 });
		break;
	}
	case WM_MBUTTONUP: {
		setKeyFlag(4, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 4 });
		break;
	}
	case WM_RBUTTONDOWN: {	//2
		setKeyFlag(2, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 2 });
		break;
	}
	case WM_RBUTTONUP: {
		setKeyFlag(2, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 2 });
		break;
	}
	case WM_KEYUP: {
		int keyNum = wParam;
		setKeyFlag(keyNum, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, keyNum });
		break;
	}
	case WM_KEYDOWN: {
		int keyNum = wParam;
		MyKey* key = new MyKey{ keyFlag(keyNum), true, keyNum };
		vec_keyBuffer.push_back(key);
		if (!keyFlag(keyNum))
			setKeyFlag(keyNum, true);
		break;
	}
	case WM_MOUSEWHEEL: {
		short delta = (short)HIWORD(wParam);
		mWheelDelta.lock();
		wheelDelta += delta;
		mWheelDelta.unlock();
		break;
	}
	case WM_CHAR: {
		WCHAR inputWChar = wParam;
		mInputWString.lock();
		inputWString += inputWChar;
		mInputWString.unlock();
		break;
	}
	case WM_CLOSE: {
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

bool MyEngine::keyFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		return key[index];
	}
	return false;
}
void MyEngine::setKeyFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		key[index] = flag;
	}
}
bool MyEngine::keyPressFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		return keyPressed[index];
	}
	return false;
}
void MyEngine::setKeyPressFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		keyPressed[index] = flag;
	}
}
bool MyEngine::keyReleaseFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		return keyReleased[index];
	}
	return false;
}
void MyEngine::setKeyReleaseFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		keyReleased[index] = flag;
	}
}

void MyEngine::drawRestart() {
	g_pSprite->End();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void MyEngine::drawRect(int x, int y, int w, int h, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
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

void MyEngine::drawBorder(int x, int y, int w, int h, int size, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
	//左侧
	drawRect(x, y, size, h, col1, col1, col4, col4);
	//右侧
	drawRect(x + w - size, y, size, h, col2, col2, col3, col3);
	//顶部
	drawRect(x + size, y, w - 2 * size, size, col1, col2, col2, col1);
	//底部
	drawRect(x + size, y + h - size, w - 2 * size, size, col4, col3, col3, col4);
}
