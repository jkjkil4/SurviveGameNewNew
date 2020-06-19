#pragma once

#include "utility.h"

#include "Class/TextureManager.h"

namespace My {
	class Engine;
}


class My::Engine {
public:
	explicit Engine();

	void onInit(HINSTANCE hInstance);
	void onDestroy();

	std::mutex mutexGameLoop;
	void funcLogic();
	void funcRender();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	//windows��һЩ����
	HWND g_hWnd = 0;
	HINSTANCE g_hInstance = 0;
	//�ӿں��豸ָ��
	D3DPRESENT_PARAMETERS d3dpp;	//����D3D�豸������
	LPDirectx g_pD3D = nullptr;			//D3D�Ľӿ�ָ�룬Ϊ�˴����豸ָ��
	LPDevice g_pDevice = nullptr;	//D3D���豸ָ�룬Ϊ�˴�������ָ��
	//��Ⱦ������
	LPTexture g_pRenderTexture = nullptr;
	LPSurface g_pRenderSurface = nullptr;
	LPSurface g_pWindowSurface = nullptr;

	//����ָ��
	LPSprite g_pSprite = nullptr;		//D3D�ľ���ָ�룬Ϊ�˻�ͼ
	LPSprite g_pSpriteRender = nullptr;	//D3D�ľ���ָ�룬������Ⱦ������

	//����
	LPD3DXFONT g_pFont = nullptr;
	LPD3DXFONT g_pFontSmall = nullptr;
	LPD3DXFONT g_pFontVerySmall = nullptr;

	//���ƾ��εĶ���Buffer
	LPDIRECT3DVERTEXBUFFER9 vbRectangle = nullptr;
	LPDIRECT3DINDEXBUFFER9 ibRectangle = nullptr;

	//����Texture
	TextureManager* renderTextureManager = nullptr;


	std::mutex mThreadCount;
	NEEDLOCK_GET_FUNC(mThreadCount, ThreadCount, threadCount, int)

	NEEDLOCK_VARIBLE_FUNC(DirectxInited, directxInited, bool)

	NEEDLOCK_VARIBLE_FUNC(NeedExit, needExit, bool)

	NEEDLOCK_VARIBLE_FUNC(DefWidth, defWidth, int)
	NEEDLOCK_VARIBLE_FUNC(DefHeight, defHeight, int)
	NEEDLOCK_VARIBLE_FUNC(ViewW, viewW, int)
	NEEDLOCK_VARIBLE_FUNC(ViewH, viewH, int)

private:
	void initWnd();
	void initDirectx();

	int threadCount = 0;

	bool directxInited = false;
	bool needExit = false;

	int defWidth = 800, defHeight = 608;
	int viewW = 800, viewH = 608;

};

namespace My {
	extern Engine engine;
}