#include "Engine/Engine.h"

#include "Room/RoomTitle.h"

using namespace My;
using namespace std;

INT WINAPI WinMain(__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in_opt LPSTR lpCmdLine,
	__in int nShowCmd)
{
#ifdef DEBUG_CONSOLE
	AllocConsole();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE* tempFile = nullptr;
	freopen_s(&tempFile, "conout$", "w+t", stdout);

	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "正在初始化" << endl;
	SetConsoleAtt(FORE_WHITE);
#endif

	engine.onInit(hInstance);
	engine.setCurrentRoom(new Room_Title);

#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "初始化完毕" << endl;
	SetConsoleAtt(FORE_WHITE);
#endif

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "正在退出" << endl;
	SetConsoleAtt(FORE_WHITE);
#endif

	engine.onDestroy();

#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "退出完毕" << endl;
	SetConsoleAtt(FORE_WHITE);
	FreeConsole();
#endif

	return 0;
}