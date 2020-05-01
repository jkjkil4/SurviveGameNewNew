#include "utility.h"
#include "MyEngine.h"
#include "MyRooms/include_rooms.h"

using namespace std;

void updateWidgetsPos();
bool canClose();

int fpsCount = 0;
int startGetFps = 0;
int fps = 0;

mutex quitMutex;


MyEngine e(updateWidgetsPos, canClose, &fps);
bool needQuit = false;
MyRoom* currentRoom = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return e.ProcWndMessage(hWnd, uMsg, wParam, lParam);
}

void changeRoom(MyRoom* room) {
	if (currentRoom) {
		currentRoom->onDestroy();
		safeDelete(currentRoom);
	}
	currentRoom = room;
}
void changeRoomByStr(string room) {
	if (room == "title") {
		changeRoom(new MyRoom_title(&e));
	}
	else if (room == "game") {
		changeRoom(new MyRoom_game(&e));
	}
	else if (room == "createSave") {
		changeRoom(new MyRoom_createSave(&e));
	}
	else if (room == "loadSave") {
		changeRoom(new MyRoom_loadSave(&e));
	}
	else if (room == "saveSave") {
		changeRoom(new MyRoom_saveSave(&e));
	}
}

void updateWidgetsPos() {
	if (currentRoom) {
		currentRoom->onResize();
		for (auto it = currentRoom->widgets.begin(); it < currentRoom->widgets.end(); it++)
			(*it)->updatePos(e.getViewW(), e.getViewH());
	}
}

bool canClose() {
	if (!currentRoom)
		return true;
	return currentRoom->canClose;
}

void mainLoop() {
	while (true) {
		if (needQuit)
			break;
		int currentTime = timeGetTime();
		if (currentRoom)
			currentRoom->onBeforeKeyCheck();
		e.onKeyCheck();
		if (currentRoom) {
			currentRoom->onLogic();
			int& sendMessage = currentRoom->sendMessage;
			if (sendMessage != 0) {
				SendMessage(e.g_hWnd, sendMessage, 0, 0);
				sendMessage = 0;
			}

			string changeRoomStr = currentRoom->getChangeRoomStr();
			if (changeRoomStr != "") {
				changeRoomByStr(changeRoomStr);
				continue;
			}

			if (e.g_hWnd) {
				if (!IsIconic(e.g_hWnd)) {
					e.renderStart();
					currentRoom->onRender();
					currentRoom->onDebug();
					e.renderEnd();
				}
			}
		}
		//计算fps
		fpsCount++;
		if (timeGetTime() - startGetFps > 1000) {
			fps = fpsCount;
			startGetFps = timeGetTime();
			fpsCount = 0;
		}
		//延时
		int elapsedTime = timeGetTime() - currentTime;
		if (elapsedTime < 16) {
			timeBeginPeriod(1);
			Sleep(16 - elapsedTime);
			timeEndPeriod(1);
		}
	}
	if (currentRoom) {
		currentRoom->onDestroy();
		safeDelete(currentRoom);
	}
	Mutex(quitMutex);
	needQuit = false;
}

INT WINAPI WinMain(__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in_opt LPSTR lpCmdLine,
	__in int nShowCmd)
{
#ifdef DEBUG_CONSOLE
	AllocConsole();
	FILE* tempFile = nullptr;
	freopen_s(&tempFile, "conout$", "w+t", stdout);
#endif

	HWND& g_hWnd = e.g_hWnd;

	//创建窗口
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
		TEXT("SurviveGameNewNew"), WS_OVERLAPPEDWINDOW, 40, 20, 
		GetSystemMetrics(SM_CXFULLSCREEN) - 80, GetSystemMetrics(SM_CYFULLSCREEN) - 40, 
		NULL, NULL, hInstance, NULL);

	//最大化
	ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);

	//得到画面宽高
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	int viewW = rect.right - rect.left;
	int viewH = rect.bottom - rect.top;
	e.setViewW(viewW);
	e.setViewH(viewH);
	e.setDefWidth(viewW);
	e.setDefHeight(viewH);

	if (g_hWnd) {
		e.g_hInstance = hInstance;
		e.onInit();
		changeRoom(new MyRoom_title(&e));
		e.setInited(true);
		UpdateWindow(g_hWnd);
	}

	//多线程
	thread thMainLoop(mainLoop);
	thMainLoop.detach();

	//消息循环
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (true) {
		if (msg.message == WM_QUIT)
			break;
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	needQuit = true;
	int _needQuit = true;
	while (_needQuit) {
		quitMutex.lock();
		_needQuit = needQuit;
		quitMutex.unlock();
		Sleep(10);
	}
	e.onDestroy();
	UnregisterClass(wc.lpszClassName, hInstance);
#ifdef DEBUG_CONSOLE
	FreeConsole();
#endif
	return 0;
}
