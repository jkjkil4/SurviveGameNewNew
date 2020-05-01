#ifndef _MYENGINE_H
#define _MYENGINE_H

#include "utility.h"
#include "MyGame/MyData.h"
#include "MyNameSpace.h"
#include "MyClasses/MyStrExpr.h"
#include "MyGame/MyGlobal.h"

#define NEEDLOCK_VARIBLE_FUNC(funcName, varibleName, varibleType)\
	std::mutex m##funcName;\
	varibleType get##funcName(){\
		m##funcName.lock();\
		varibleType temp = varibleName;\
		m##funcName.unlock();\
		return temp;\
	}\
	void set##funcName(varibleType _var){\
		m##funcName.lock();\
		varibleName = _var;\
		m##funcName.unlock();\
	}
/*
	��Ҫ�ͷŵĶ���
	g_pD3D, g_pDevice, 
	g_pSprite, g_pSpriteRender,
	g_pRenderTexture, g_pRenderSurface, g_pWindowSurface,

	g_pFont

	vbRectangle
	ibRectangle
*/
class MyEngine
{
private:
	bool hasFocus = true, inited = false;
	int doneTime = 0, resizeTime = timeGetTime();
	int defWidth = 800, defHeight = 608;
	int viewW = 800, viewH = 608;
	//����
	int wheelDelta = 0;
	//������ַ�
	std::wstring inputWString = TEXT("");

public:
	explicit MyEngine(void (*signalScaled)(), bool(*canClose)(), int* fps);

	std::mutex changeRoomMutex;
	NEEDLOCK_VARIBLE_FUNC(HasFocus, hasFocus, bool);
	NEEDLOCK_VARIBLE_FUNC(Inited, inited, bool);
	NEEDLOCK_VARIBLE_FUNC(DoneTime, doneTime, int);
	NEEDLOCK_VARIBLE_FUNC(ResizeTime, resizeTime, int);
	NEEDLOCK_VARIBLE_FUNC(DefWidth, defWidth, int);
	NEEDLOCK_VARIBLE_FUNC(DefHeight, defHeight, int);
	NEEDLOCK_VARIBLE_FUNC(ViewW, viewW, int);
	NEEDLOCK_VARIBLE_FUNC(ViewH, viewH, int);
	NEEDLOCK_VARIBLE_FUNC(WheelDelta, wheelDelta, int);
	NEEDLOCK_VARIBLE_FUNC(InputWString, inputWString, std::wstring);

	void onInit();
	void renderStart();
	void renderEnd();
	void onDestroy();

	LRESULT ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//����
	void drawRestart();
	void drawRect(int x, int y, int w, int h, DWORD col1 = 0xffffffff, DWORD col2 = 0xffffffff, DWORD col3 = 0xffffffff, DWORD col4 = 0xffffffff);
	void drawBorder(int x, int y, int w, int h, int size, DWORD col1 = 0xff000000, DWORD col2 = 0xff000000, DWORD col3 = 0xff000000, DWORD col4 = 0xff000000);

	//------------------------------------------------------------------------------------//
	
	//ȫ�ֱ���
	MyGlobal global;

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
	//���ʱ����ɫ
	D3DCOLOR clearColor = D3DCOLOR_XRGB(102, 204, 255);

	//һЩ����
	void (*signalScaled)() = nullptr;
	bool (*canClose)() = nullptr;

	//�������
	bool keyFlag(int num);
	void setKeyFlag(int num, bool flag);
	bool keyPressFlag(int num);
	void setKeyPressFlag(int num, bool flag);
	bool keyReleaseFlag(int num);
	void setKeyReleaseFlag(int num, bool flag);
	std::vector<MyKey*> vec_keyBuffer;
	static constexpr int keyNumber = 0x88;
	bool key[keyNumber];
	bool keyPressed[keyNumber];
	bool keyReleased[keyNumber];
	static constexpr int mice[3]{ VK_LBUTTON, VK_MBUTTON, VK_RBUTTON };

	//���λ��
	int mouseX = -1;
	int mouseY = -1;

	//����
	LPD3DXFONT g_pFont = nullptr;
	LPD3DXFONT g_pFontSmall = nullptr;
	LPD3DXFONT g_pFontVerySmall = nullptr;

	//���ƾ��εĶ���Buffer
	LPDIRECT3DVERTEXBUFFER9 vbRectangle;
	LPDIRECT3DINDEXBUFFER9 ibRectangle;

	//pointer
	int* fps = nullptr;
};


#endif //_MYENGINE_H