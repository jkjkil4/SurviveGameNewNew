#include "Engine.h"

using namespace My;


LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return engine.ProcWndMessage(hWnd, uMsg, wParam, lParam);
}


#define MOUSE_CHECK(btn)\
	case WM_##btn##DOWN:\
		setKey(VK_##btn);\
		vecKeyBuffer.push_back(Key(VK_##btn, Key::State::Press, false));\
		break;\
	case WM_##btn##UP:\
		setKey(VK_##btn, false);\
		vecKeyBuffer.push_back(Key(VK_##btn, Key::State::Release, false));\
		break

LRESULT CALLBACK Engine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	#pragma region 响应鼠标和键盘
		MOUSE_CHECK(LBUTTON);
		MOUSE_CHECK(MBUTTON);
		MOUSE_CHECK(RBUTTON);
	case WM_MOUSEMOVE:
		
		break;
	case WM_KEYDOWN: {
		int keyNum = wParam;
		bool isAutoRepeat = false;
		if (isKey(keyNum)) {
			isAutoRepeat = true;
		}
		else {
			setKey(keyNum);
		}
		vecKeyBuffer.push_back(Key(keyNum, Key::State::Press, isAutoRepeat));
		break;
	}
	case WM_KEYUP: {
		int keyNum = wParam;
		setKey(keyNum, false);
		vecKeyBuffer.push_back(Key(keyNum, Key::State::Release));
		break;
	}
	#pragma endregion
	case WM_SIZE: {//大小被改变
		if (getWndInited()) {
			//setResizeTime(timeGetTime());
			D3DXMATRIX g_scale;
			RECT rect;
			GetClientRect(g_hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			setViewW(w);
			setViewH(h);
			setSpriteScale(g_pSpriteRender, 0, 0, (float)getDefWidth() / w, (float)getDefHeight() / h);
			addEvent(&Engine::evResized, true);
		}
		break;
	}
	case WM_CLOSE: {
		setClosed(true);
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#undef MOUSE_CHECK