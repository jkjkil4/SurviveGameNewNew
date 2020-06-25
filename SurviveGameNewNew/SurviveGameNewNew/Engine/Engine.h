#pragma once

#include "../utility.h"

#include "../NameSpace.h"
#include "../Class/TextureManager.h"
#include "../Class/LimitSizeVector.h"
#include "../Class/Delayer.h"

namespace My {
	struct Key;

	class Engine;
}


struct My::Key {
public:
	enum class State { Press, Release };

	Key(int key, State state, bool isAutoRepeat = false)
		: key(key), state(state), isAutoRepeat(isAutoRepeat) {}

	int key = 0;
	State state = State::Press;
	bool isAutoRepeat = false;
};


class My::Engine {
public:
	explicit Engine();

	void onInit(HINSTANCE hInstance);
	void onDestroy();

	void onLogic();
	void onRender();

	void onRenderStart();	//��Ⱦ��ʼ
	void onRenderEnd(RenderError& err);	//��Ⱦ����

	std::mutex mutexGameLoop;
	void funcLogic();
	void funcRender();

	//����
	void drawRestart();
	void drawRect(int x, int y, int w, int h, DWORD col1 = 0xffffffff, DWORD col2 = 0xffffffff, DWORD col3 = 0xffffffff, DWORD col4 = 0xffffffff);
	void drawBorder(int x, int y, int w, int h, int size, DWORD col = 0xff000000);

	HRESULT resetDevice();
	void onResetingDevice();

	LRESULT CALLBACK ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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

	//���ʱ����ɫ
	D3DCOLOR clearColor = D3DCOLOR_XRGB(102, 204, 255);

	//����
	bool isKeyPressed(int num);
	bool isKey(int num);
	bool isKeyReleased(int num);
	void setKeyPressed(int num, bool on = true);
	void setKey(int num, bool on = true);
	void setKeyReleased(int num, bool on = true);
	std::vector<Key> vecKeyBuffer;
	SC int keyNumber = 0x88;
	std::mutex mutexKeyPressed;
	std::mutex mutexKey;
	std::mutex mutexKeyReleased;
	bool keyPressed[keyNumber];
	bool key[keyNumber];
	bool keyReleased[keyNumber];


	std::mutex mutexThreadCount;
	NEEDLOCK_GET_FUNC(mutexThreadCount, ThreadCount, threadCount, int)

	NEEDLOCK_VARIBLE_FUNC(WndInited, wndInited, bool)
	NEEDLOCK_VARIBLE_FUNC(DirectxInited, directxInited, bool)

	NEEDLOCK_VARIBLE_FUNC(NeedExit, needExit, bool)
	NEEDLOCK_VARIBLE_FUNC(Closed, closed, bool)

	NEEDLOCK_VARIBLE_FUNC(ResizeTime, resizeTime, int)

	NEEDLOCK_VARIBLE_FUNC(LogicFps, logicFps, int)
	NEEDLOCK_VARIBLE_FUNC(RenderFps, renderFps, int)

	NEEDLOCK_VARIBLE_FUNC(DefWidth, defWidth, int)
	NEEDLOCK_VARIBLE_FUNC(DefHeight, defHeight, int)
	NEEDLOCK_VARIBLE_FUNC(ViewW, viewW, int)
	NEEDLOCK_VARIBLE_FUNC(ViewH, viewH, int)

private:
	void initWnd();
	void initDirectx();

	std::thread* thLogic = nullptr, * thRender = nullptr;	//�ֱ����߼��������Ⱦ���߳�

	std::mutex mutexLogicRender;	//�߼��������Ⱦ֮����߳���
//#ifdef DEBUG_CONSOLE
//	std::mutex mutexConsoleOutput;	//�������̨���߳���
//#endif

	int threadCount = 0;	//���߳�����

	bool wndInited = false, directxInited = false;	//�ֱ��Ǵ��ڡ�ͼ�ν����Ƿ񱻳�ʼ��
	bool needExit = false;	//�Ƿ���Ҫ�˳������������߳��˳�
	bool closed = false;	//�Ƿ�ر��˴���

	int resizeTime = 0;	//��С�ı��Ǽ�¼��ʱ��

	int logicFps = -1, renderFps = -1;	//�ֱ����߼�����Ⱦ��֡��

	int defWidth = 800, defHeight = 608;	//Ĭ�Ͽ��
	int viewW = 800, viewH = 608;	//��Ұ���

	//�����洢Present��ʱ��vector
	LimitSizeVector<double> vecRenderPresentTime = LimitSizeVector<double>(20);
};

namespace My {
	extern Engine engine;
}