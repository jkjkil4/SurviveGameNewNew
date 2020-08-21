#include "Engine.h"

#include "../Room/Room.h"

using namespace My;
using namespace std;

Engine My::engine;


Engine::Engine() {
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	clearKeys();
}



void Engine::onLogic() {
	mutexEvent.lock();
	for (auto func : vecEvents)
		(this->*func)();
	vecEvents.clear();
	mutexEvent.unlock();

	//处理按键
	ZeroMemory(keyPressed, sizeof(keyPressed));
	ZeroMemory(keyReleased, sizeof(keyReleased));
	//设置按键Pressed和Released的状态
	for (auto it = vecKeyBuffer.begin(); it < vecKeyBuffer.end(); it++) {
		Key key = *it;
		if (!key.isAutoRepeat) {
			if (key.state == Key::State::Press)
				setKeyPressed(key.key);
			else setKeyReleased(key.key);
		}
	}

	//得到鼠标位置
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(g_hWnd, &mPos);
	mouseX = mPos.x;
	mouseY = mPos.y;

	//调用Room的Logic
	if (currentRoom) {
		try {
			currentRoom->onLogic();
		}
		catch (RoomGoto roomGoto) {
			if (roomGoto.room) {
				setCurrentRoom(roomGoto.room);
			}
			else SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		//调用控件的按键处理函数
		for (auto it = vecKeyBuffer.begin(); it < vecKeyBuffer.end(); it++) {
			currentRoom->evKey(&*it);
		}

		//调用控件的鼠标滚轮函数
		mutexWheelDelta.lock();
		if (wheelDelta != 0) {
			currentRoom->evMouseWheel(wheelDelta);
			wheelDelta = 0;
		}
		mutexWheelDelta.unlock();

		//调用控件的文字输入函数
		mutexInputWStr.lock();
		if (inputWStr.length() != 0) {
			currentRoom->evTextInput(inputWStr);
			inputWStr = _T("");
		}
		mutexInputWStr.unlock();
	}
	//清空KeyBuffer
	vecKeyBuffer.clear();
}

void Engine::onRender() {
	if (currentRoom) {
		currentRoom->onRender();
	}
}


void Engine::onRenderStart() {
	pCurPST = nullptr;
	pCurVST = nullptr;
	//填充
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, clearColor, 1.0f, 0);
	//开始绘制
	engine.drawBegin();
}

void Engine::onRenderEnd(RenderError& err) {
	//结束绘制
	g_pSprite->End();
	//将纹理绘制到窗口
	g_pDevice->SetRenderTarget(0, g_pWindowSurface);	//设置为绘制到窗口
	g_pDevice->BeginScene();	//获取绘制权限
	g_pSpriteRender->Begin(0);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//结束绘制

	Counter counter;
	counter.start();
	HRESULT hr = g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	vecRenderPresentTime.addElement(counter.getTime());

	if (FAILED(hr) && !getClosed())
		err = RenderError::ErrorCannotPresent;

	g_pDevice->SetRenderTarget(0, g_pRenderSurface);	//设置为绘制到g_pRenderSurface
	
}

HRESULT Engine::resetDevice() {
	//检查设备状态
	HRESULT hr = g_pDevice->TestCooperativeLevel();

	//设备能被Reset
	if (hr == D3DERR_DEVICENOTRESET) {
		onResetingDevice();
	}
	else if (hr == D3DERR_DEVICELOST) {
		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_RED + FORE_LIGHT);
		cout << "Device Lost" << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif

		Sleep(25);
	}

	return hr;
}


void Engine::onResetingDevice() {
	int startTime = timeGetTime();

	#ifdef DEBUG_CONSOLE
	SetConsoleAtt(FORE_WHITE + FORE_LIGHT);
	cout << "Is Reseting Device" << endl;
	SetConsoleAtt(FORE_WHITE);
	#endif

	g_pSprite->OnLostDevice();
	g_pSpriteRender->OnLostDevice();
	g_pFont->OnLostDevice();
	g_pFontSmall->OnLostDevice();
	g_pFontVerySmall->OnLostDevice();
	TextureManager::onReleaseTextures();

retry:
	//Reset设备
	HRESULT hr2;
	//int times = 0;
	//for (int i = 0; i < 10; i++) {
	hr2 = g_pDevice->Reset(&d3dpp);
	//	times++;
	//	if (SUCCEEDED(hr2))
	//		break;
	//}
	if (SUCCEEDED(hr2)) {
		//Reset设备成功
		g_pSprite->OnResetDevice();
		g_pSpriteRender->OnResetDevice();
		g_pFont->OnResetDevice();
		g_pFontSmall->OnResetDevice();
		g_pFontVerySmall->OnResetDevice();
		TextureManager::onResetTextures();

		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_GREEN + FORE_LIGHT);
		cout << "Reset Device 成功"/*"\t  本次尝试次数(最大10):" << times <<*/ "\t  本次消耗时间(ms):" << timeGetTime() - startTime << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif
	}
	else {
		//Reset设备失败
		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_RED + FORE_LIGHT);
		cout << "Reset Device 失败\t" << hr2 << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif

		int res = MessageBox(nullptr, TEXT("重置设备失败\n\n重试? (取消则会退出)"), TEXT("错误"), MB_OKCANCEL);
		if (res == 1) {
			goto retry;
		}
		else {
			SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
	}
}