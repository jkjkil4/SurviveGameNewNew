#include "MyEngine.h"

using namespace std;

MyEngine::MyEngine(void (*signalScaled)(), int* fps) {
	this->fps = fps;
	this->signalScaled = signalScaled;
	for (int i = 0; i < 123; i++) {
		keyPressed[i] = false;
		keyReleased[i] = false;
		key[i] = false;
	}
}

void MyEngine::onInit() {
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
		D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &g_pRenderTexture, NULL
		);
	//得到纹理的Surface
	g_pRenderTexture->GetSurfaceLevel(0, &g_pRenderSurface);
	//得到设备的Surface
	g_pDevice->GetRenderTarget(0, &g_pWindowSurface);
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);

	//初始化字体
	D3DXCreateFont(g_pDevice, 20, 10, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFont);
	D3DXCreateFont(g_pDevice, 12, 6, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFontSmall);

	//其他操作
	data.onInit("data\\texture", g_pDevice);
	doneTime = timeGetTime();
}
void MyEngine::onKeyCheck() {
	for (int i = 0; i < 123; i++) {
		keyPressed[i] = false;
		keyReleased[i] = false;
	}
	for (auto it = vec_keyBuffer.begin(); it < vec_keyBuffer.end(); it++) {
		MyKey* key = *it;
		if (key->isForWidget)
			continue;
		key->flag ? setKeyPressFlag(key->key, true) : setKeyReleaseFlag(key->key, true);
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
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
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
	//销毁
	for (auto it = vec_keyBuffer.begin(); it < vec_keyBuffer.end(); it++)
		delete(*it);
	vec_keyBuffer.clear();
	//destroy
	data.onDestroy();
}

LRESULT MyEngine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
		if (isInited) {
			resizeTime = timeGetTime();
			D3DXMATRIX g_scale;
			RECT rect;
			GetClientRect(g_hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			viewW = w;
			viewH = h;
			mySetScale(g_pSpriteRender, 0, 0, (float)defWidth / w, (float)defHeight / h);
			signalScaled();
		}
		break;
	}
	case WM_LBUTTONDOWN:	//1
		setKeyFlag(1, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 1 });
		break;
	case WM_LBUTTONUP:
		setKeyFlag(1, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 1 });
		break;
	case WM_MBUTTONDOWN:	//4
		setKeyFlag(4, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 4 });
		break;
	case WM_MBUTTONUP:
		setKeyFlag(4, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 4 });
		break;
	case WM_RBUTTONDOWN:	//2
		setKeyFlag(2, true);
		vec_keyBuffer.push_back(new MyKey{ false, true, 2 });
		break;
	case WM_RBUTTONUP:
		setKeyFlag(2, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, 2 });
		break;
	case WM_KEYUP:{
		int keyNum = wParam;
		setKeyFlag(keyNum, false);
		vec_keyBuffer.push_back(new MyKey{ false, false, keyNum });
		break;
	}
	case WM_KEYDOWN:{
		int keyNum = wParam;
		if (keyFlag(keyNum))
			setKeyFlag(keyNum, true);
		MyKey* key = new MyKey{ keyFlag(keyNum), true, keyNum };
		vec_keyBuffer.push_back(key);
		break;
	}
	case WM_CHAR: {
		WCHAR inputWChar = wParam;
		inputWString += inputWChar;
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool MyEngine::keyFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		return key[index];
	}
	return false;
}
void MyEngine::setKeyFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		key[index] = flag;
	}
}
bool MyEngine::keyPressFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		return keyPressed[index];
	}
	return false;
}
void MyEngine::setKeyPressFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		keyPressed[index] = flag;
	}
}
bool MyEngine::keyReleaseFlag(int num) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		return keyReleased[index];
	}
	return false;
}
void MyEngine::setKeyReleaseFlag(int num, bool flag) {
	int index = num - 1;
	if (index >= 0 && index < 123) {
		keyReleased[index] = flag;
	}
}

void MyEngine::drawRect(int x, int y, int w, int h) {
	g_pSprite->End();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DVERTEXBUFFER9 vb;
	g_pDevice->CreateVertexBuffer(4 * sizeof(Vertex), 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &vb, nullptr);
	LPDIRECT3DINDEXBUFFER9 ib;
	g_pDevice->CreateIndexBuffer(6 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, 0);

	Vertex* vertexs;
	vb->Lock(0, 0, (void**)&vertexs, 0);
	
	vertexs[0] = Vertex((float)x, (float)y, 0.0f);
	vertexs[1] = Vertex((float)(x + w), (float)y, 0.0f);
	vertexs[2] = Vertex((float)(x + w), (float)(y + h), 0.0f);
	vertexs[3] = Vertex((float)x, (float)(y + h), 0.0f);

	vb->Unlock();

	WORD* index = nullptr;
	ib->Lock(0, 0, (void**)&index, 0);
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	
	index[3] = 0;
	index[4] = 2;
	index[5] = 3;
	ib->Unlock();
	
	g_pDevice->SetFVF(D3DFVF_XYZ);
	g_pDevice->SetStreamSource(0, vb, 0, sizeof(Vertex));
	g_pDevice->SetIndices(ib);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	vb->Release();
	ib->Release();
}
