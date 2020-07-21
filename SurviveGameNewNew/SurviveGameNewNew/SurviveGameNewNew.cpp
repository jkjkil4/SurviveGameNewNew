#include "Engine/Engine.h"
#include "Game/Data.h"

#include "Room/RoomTitle.h"

using namespace My;
using namespace std;

#define DEBUG_MEMSIZE

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

#ifdef DEBUG_MEMSIZE
	cout << "----MemSize----" << endl;
	cout << "Engine:\t" << sizeof(Engine) << endl;
	cout << "Room:\t" << sizeof(Room) << endl;
	cout << "Widget:\t" << sizeof(Widget) << endl;
	cout << "---------------" << endl;
#endif

	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "���ڳ�ʼ��" << endl;
	SetConsoleAtt(FORE_WHITE);
#endif

	engine.onInit(hInstance);
	gameData.onInit();
	engine.setCurrentRoom(new Room_Title);

#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "��ʼ�����" << endl;
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
	cout << "�����˳�" << endl;
	SetConsoleAtt(FORE_WHITE);
#endif

	gameData.onDestroy();
	engine.onDestroy();

#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "�˳����" << endl;
	SetConsoleAtt(FORE_WHITE);
	FreeConsole();
#endif

	return 0;
}