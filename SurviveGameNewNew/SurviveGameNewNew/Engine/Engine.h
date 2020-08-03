#pragma once

#include "../utility.h"

#include "../NameSpace.h"
#include "../Class/TextureManager.h"
#include "../Class/LimitSizeVector.h"
#include "../Class/Delayer.h"

namespace My {
	struct Key;

	class Engine;
	typedef void(Engine::* EngineFunc)();

	class Room;
	struct PixelShader_Table;
	struct VertexShader_Table;
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

	void onRenderStart();	//渲染开始
	void onRenderEnd(RenderError& err);	//渲染结束

	std::mutex mutexGameLoop;
	void funcLogic();
	void funcRender();

	HRESULT resetDevice();
	void onResetingDevice();

	LRESULT CALLBACK ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	#pragma region 一些变量
	//windows的一些东西
	HWND g_hWnd = 0;
	HINSTANCE g_hInstance = 0;
	//接口和设备指针
	D3DPRESENT_PARAMETERS d3dpp;	//描述D3D设备的能力
	LPDirectx g_pD3D = nullptr;			//D3D的接口指针，为了创建设备指针
	LPDevice g_pDevice = nullptr;	//D3D的设备指针，为了创建精灵指针
	//渲染到纹理
	LPTexture g_pRenderTexture = nullptr;
	LPSurface g_pRenderSurface = nullptr;
	LPSurface g_pWindowSurface = nullptr;

	//精灵指针
	LPSprite g_pSprite = nullptr;		//D3D的精灵指针，为了画图
	LPSprite g_pSpriteRender = nullptr;	//D3D的精灵指针，用来渲染到纹理

	//字体
	LPFont g_pFont = nullptr;
	LPFont g_pFontSmall = nullptr;
	LPFont g_pFontVerySmall = nullptr;

	//管理Texture
	TextureManager* renderTextureManager = nullptr;
	#pragma endregion

	#pragma region 绘制相关
	void setBlendMode(D3DBLEND srcBlend, D3DBLEND destBlend);

	void setPixelShader(PixelShader_Table* pst);
	PixelShader_Table* pCurPST = nullptr;
	void setVertexShader(VertexShader_Table* vst);
	VertexShader_Table* pCurVST = nullptr;

	void drawBegin();
	void drawRestart();
	void drawRect(int x, int y, int w, int h, DWORD col);
	void drawRect(int x, int y, int w, int h, DWORD col1, DWORD col2, DWORD col3, DWORD col4);
	void drawBorder(int x, int y, int w, int h, int size, DWORD col = 0xff000000);
	//绘制矩形的顶点Buffer
	LPDIRECT3DVERTEXBUFFER9 vbRectangle = nullptr;
	LPDIRECT3DINDEXBUFFER9 ibRectangle = nullptr;
	//清空时的颜色
	D3DCOLOR clearColor = D3DCOLOR_XRGB(102, 204, 255);
	#pragma endregion

	#pragma region 按键处理
	bool isKeyPressed(int num);
	bool isKey(int num);
	bool isKeyReleased(int num);
	void setKeyPressed(int num, bool on = true);
	void setKey(int num, bool on = true);
	void setKeyReleased(int num, bool on = true);
	void clearKeys();
	std::vector<Key> vecKeyBuffer;
	SC int keyNumber = 0x88;
	std::mutex mutexKeyPressed;
	std::mutex mutexKey;
	std::mutex mutexKeyReleased;
	bool keyPressed[keyNumber];
	bool key[keyNumber];
	bool keyReleased[keyNumber];
	int mouseX = -1, mouseY = -1;
	#pragma endregion

	#pragma region Room相关
	void setCurrentRoom(Room* room);
	Room* currentRoom = nullptr;
	#pragma endregion

	#pragma region Event相关
	void addEvent(EngineFunc func, bool single = false);
	void evResized();
	std::mutex mutexEvent;
	std::vector<EngineFunc> vecEvents;
	#pragma endregion

	void setCursorShape(LPCWSTR shape);
	LPCWSTR curCursorShape = IDC_ARROW;

	void showMsgBox(std::wstring text);
	void showMsgBox(std::wstring caption, std::wstring text, UINT btns);

	#pragma region 获取和设定变量的函数
	//std::mutex mutexThreadCount;
	//NEEDLOCK_GET_FUNC(mutexThreadCount, ThreadCount, threadCount, int)

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
	#pragma endregion

private:
	void initWnd();
	void initDirectx();

	std::thread* thLogic = nullptr, * thRender = nullptr;	//分别是逻辑处理和渲染的线程

	std::mutex mutexLogicRender;	//逻辑处理和渲染之间的线程锁

	//int threadCount = 0;	//子线程数量

	bool wndInited = false, directxInited = false;	//分别是窗口、图形界面是否被初始化
	bool needExit = false;	//是否需要退出，用来让子线程退出
	bool closed = false;	//是否关闭了窗口

	int resizeTime = 0;	//大小改变是记录的时间

	int logicFps = -1, renderFps = -1;	//分别是逻辑和渲染的帧率

	int defWidth = 800, defHeight = 608;	//默认宽高
	int viewW = 800, viewH = 608;	//视野宽高

	bool isWndResized = false;

	//用来存储Present耗时的vector
	LimitSizeVector<double> vecRenderPresentTime = LimitSizeVector<double>(20);
};

namespace My {
	extern Engine engine;
}