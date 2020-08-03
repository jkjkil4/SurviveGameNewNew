#include "Engine.h"

#include "../Room/Room.h"

using namespace My;
using namespace std;

void Engine::setCurrentRoom(Room* room) {
	if (currentRoom) {
		currentRoom->onDestroy();
		safeDelete(currentRoom);
	}
	currentRoom = room;
}


void Engine::addEvent(EngineFunc func, bool single) {
	mutexEvent.lock();
	if (single) {
		for (auto it = vecEvents.begin(); it < vecEvents.end(); it++) {
			if (*it == func) {
				mutexEvent.unlock();
				return;
			}
		}
	}
	vecEvents.push_back(func);
	mutexEvent.unlock();
}

void Engine::evResized() {
	if (currentRoom) {
		currentRoom->evResized();
	}
}


void Engine::setCursorShape(LPCWSTR shape) {
	if (curCursorShape != shape) {
		SetClassLong(g_hWnd, GCL_HCURSOR, (long)LoadCursor(NULL, shape));
		curCursorShape = shape;
	}
}


void Engine::showMsgBox(wstring text) {
	MessageBox(g_hWnd, text.c_str(), _T(""), MB_OK);
}

void Engine::showMsgBox(wstring caption, wstring text, UINT btns) {
	MessageBox(g_hWnd, text.c_str(), caption.c_str(), btns);
}