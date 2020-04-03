#ifndef _MYENGINE_H
#define _MYENGINE_H

#include "utility.h"
#include "MyGame/MyData.h"
/*
	��Ҫ�ͷŵĶ���
	g_pD3D, g_pDevice, 
	g_pSprite, g_pSpriteRender,
	g_pRenderTexture, g_pRenderSurface, g_pWindowSurface
*/
class MyEngine
{
private:
	struct MyKey {
		bool flag;
		int key;
	};

public:
	explicit MyEngine(void (*signalScaled)(), int* fps);

	void onInit();
	void renderStart();
	void renderEnd();
	void onDestroy();

	LRESULT ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//------------------------------------------------------------------------------------//
	int defWidth = 800, defHeight = 608;
	int viewW = 800, viewH = 608;
	//windows��һЩ����
	HWND g_hWnd = 0;
	HINSTANCE g_hInstance = 0;
	//�ӿں��豸ָ��
	LPDIRECT3D9 g_pD3D = nullptr;			//D3D�Ľӿ�ָ�룬Ϊ�˴����豸ָ��
	LPDIRECT3DDEVICE9 g_pDevice = nullptr;	//D3D���豸ָ�룬Ϊ�˴�������ָ��
	//����ָ��
	LPD3DXSPRITE g_pSprite = nullptr;		//D3D�ľ���ָ�룬Ϊ�˻�ͼ
	LPD3DXSPRITE g_pSpriteRender = nullptr;	//D3D�ľ���ָ�룬������Ⱦ������
	// ��Ⱦ������
	IDirect3DTexture9* g_pRenderTexture = nullptr;
	IDirect3DSurface9* g_pRenderSurface = nullptr;
	IDirect3DSurface9* g_pWindowSurface = nullptr;
	//����
	void onKeyCheck();
	//��ͼ
	MyData data;
	//һЩ����
	int doneTime = 0, resizeTime = timeGetTime();
	bool isInited = false;
	bool hasFocus = true;
	void (*signalScaled)() = nullptr;
	//�������
	bool keyFlag(int num);
	void setKeyFlag(int num, bool flag);
	bool keyPressFlag(int num);
	void setKeyPressFlag(int num, bool flag);
	bool keyReleaseFlag(int num);
	void setKeyReleaseFlag(int num, bool flag);
	std::vector<MyKey*> vec_keyBuffer;
	bool key[123];
	bool keyPressed[123];
	bool keyReleased[123];
	//���λ��
	int mouseX = -1;
	int mouseY = -1;

	//pointer
	int* fps = nullptr;
};


#endif //_MYENGINE_H