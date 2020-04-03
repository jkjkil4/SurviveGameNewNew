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
	//����D3D�ӿ�ָ��
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;		//D3D��ʾģʽ�ṹ��
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	//��ȡ��ǰ�Կ�����ʾģʽ
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//����D3D���豸ָ��
	D3DPRESENT_PARAMETERS d3dpp;	//����D3D�豸������
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = defWidth;
	d3dpp.BackBufferHeight = defHeight;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//��תЧ��������

	//�����豸ָ��
	g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,		//Ĭ���Կ�
		D3DDEVTYPE_HAL,			//Ӳ�������
		g_hWnd,					//�������Ĵ��ڣ�Ҫ����Ĵ��ڣ�
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//������������ģʽ
		&d3dpp,		//�豸������
		&g_pDevice	//���ص��豸ָ��
		);

	//��������ָ��
	D3DXCreateSprite(g_pDevice, &g_pSprite);
	D3DXCreateSprite(g_pDevice, &g_pSpriteRender);

	//"��Ⱦ������"
	g_pDevice->CreateTexture(
		GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), 2,
		D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &g_pRenderTexture, NULL
		);
	//�õ�������Surface
	g_pRenderTexture->GetSurfaceLevel(0, &g_pRenderSurface);
	//�õ��豸��Surface
	g_pDevice->GetRenderTarget(0, &g_pWindowSurface);
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);

	//��������
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
	//���
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	//��ʼ����
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void MyEngine::renderEnd() {
	//��������
	g_pSprite->End();
	//���������Ƶ�����
	g_pDevice->SetRenderTarget(0, g_pWindowSurface);	//����Ϊ���Ƶ�����
	g_pDevice->BeginScene();	//��ȡ����Ȩ��
	g_pSpriteRender->Begin(0);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//��������
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//ǰ��̨������������"Դ����"
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);	//����Ϊ���Ƶ�g_pRenderSurface
}
void MyEngine::onDestroy() {
	//�ͷ�
	safeRelease(g_pD3D);
	safeRelease(g_pDevice);
	safeRelease(g_pSprite);
	safeRelease(g_pSpriteRender);
	safeRelease(g_pRenderTexture);
	safeRelease(g_pRenderSurface);
	safeRelease(g_pWindowSurface);
	//����
	for (auto it = vec_keyBuffer.begin(); it < vec_keyBuffer.end(); it++)
		delete(*it);
	vec_keyBuffer.clear();
	//destroy
	data.onDestroy();
}

LRESULT MyEngine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		//------������------
	case WM_KILLFOCUS:
		hasFocus = false;
		break;
	case WM_SETFOCUS:
		hasFocus = true;
		break;
		//------��С���ı�----
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
		vec_keyBuffer.push_back(new MyKey{ true, 1 });
		break;
	case WM_LBUTTONUP:
		setKeyFlag(1, false);
		vec_keyBuffer.push_back(new MyKey{ false, 1 });
		break;
	case WM_MBUTTONDOWN:	//4
		setKeyFlag(4, true);
		vec_keyBuffer.push_back(new MyKey{ true, 4 });
		break;
	case WM_MBUTTONUP:
		setKeyFlag(4, false);
		vec_keyBuffer.push_back(new MyKey{ false, 4 });
		break;
	case WM_RBUTTONDOWN:	//2
		setKeyFlag(2, true);
		vec_keyBuffer.push_back(new MyKey{ true, 2 });
		break;
	case WM_RBUTTONUP:
		setKeyFlag(2, false);
		vec_keyBuffer.push_back(new MyKey{ false, 2 });
		break;
	case WM_KEYUP:{
		int keyNum = wParam;
		setKeyFlag(keyNum, false);
		vec_keyBuffer.push_back(new MyKey{ false, keyNum });
		break;
	}
	case WM_KEYDOWN:{
		int keyNum = wParam;
		if (keyFlag(keyNum))
			break;
		setKeyFlag(keyNum, true);
		MyKey* key = new MyKey{ true, keyNum };
		vec_keyBuffer.push_back(key);
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