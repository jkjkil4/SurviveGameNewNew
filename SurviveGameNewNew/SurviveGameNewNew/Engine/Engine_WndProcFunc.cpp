#include "Engine.h"

using namespace My;


LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return engine.ProcWndMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Engine::ProcWndMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	#pragma region 响应鼠标和键盘
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
			//TODO: 调整控件的位置
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