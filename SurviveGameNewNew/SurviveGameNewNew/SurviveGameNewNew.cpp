#include "Engine.h"

using namespace My;

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

	engine.onInit(hInstance);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	engine.onDestroy();

#ifdef DEBUG_CONSOLE
	FreeConsole();
#endif
	
	return 0;
}