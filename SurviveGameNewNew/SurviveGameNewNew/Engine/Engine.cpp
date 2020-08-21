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

	//������
	ZeroMemory(keyPressed, sizeof(keyPressed));
	ZeroMemory(keyReleased, sizeof(keyReleased));
	//���ð���Pressed��Released��״̬
	for (auto it = vecKeyBuffer.begin(); it < vecKeyBuffer.end(); it++) {
		Key key = *it;
		if (!key.isAutoRepeat) {
			if (key.state == Key::State::Press)
				setKeyPressed(key.key);
			else setKeyReleased(key.key);
		}
	}

	//�õ����λ��
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(g_hWnd, &mPos);
	mouseX = mPos.x;
	mouseY = mPos.y;

	//����Room��Logic
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
		//���ÿؼ��İ���������
		for (auto it = vecKeyBuffer.begin(); it < vecKeyBuffer.end(); it++) {
			currentRoom->evKey(&*it);
		}

		//���ÿؼ��������ֺ���
		mutexWheelDelta.lock();
		if (wheelDelta != 0) {
			currentRoom->evMouseWheel(wheelDelta);
			wheelDelta = 0;
		}
		mutexWheelDelta.unlock();

		//���ÿؼ����������뺯��
		mutexInputWStr.lock();
		if (inputWStr.length() != 0) {
			currentRoom->evTextInput(inputWStr);
			inputWStr = _T("");
		}
		mutexInputWStr.unlock();
	}
	//���KeyBuffer
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
	//���
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, clearColor, 1.0f, 0);
	//��ʼ����
	engine.drawBegin();
}

void Engine::onRenderEnd(RenderError& err) {
	//��������
	g_pSprite->End();
	//��������Ƶ�����
	g_pDevice->SetRenderTarget(0, g_pWindowSurface);	//����Ϊ���Ƶ�����
	g_pDevice->BeginScene();	//��ȡ����Ȩ��
	g_pSpriteRender->Begin(0);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//��������

	Counter counter;
	counter.start();
	HRESULT hr = g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//ǰ��̨������������"Դ����"
	vecRenderPresentTime.addElement(counter.getTime());

	if (FAILED(hr) && !getClosed())
		err = RenderError::ErrorCannotPresent;

	g_pDevice->SetRenderTarget(0, g_pRenderSurface);	//����Ϊ���Ƶ�g_pRenderSurface
	
}

HRESULT Engine::resetDevice() {
	//����豸״̬
	HRESULT hr = g_pDevice->TestCooperativeLevel();

	//�豸�ܱ�Reset
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
	//Reset�豸
	HRESULT hr2;
	//int times = 0;
	//for (int i = 0; i < 10; i++) {
	hr2 = g_pDevice->Reset(&d3dpp);
	//	times++;
	//	if (SUCCEEDED(hr2))
	//		break;
	//}
	if (SUCCEEDED(hr2)) {
		//Reset�豸�ɹ�
		g_pSprite->OnResetDevice();
		g_pSpriteRender->OnResetDevice();
		g_pFont->OnResetDevice();
		g_pFontSmall->OnResetDevice();
		g_pFontVerySmall->OnResetDevice();
		TextureManager::onResetTextures();

		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_GREEN + FORE_LIGHT);
		cout << "Reset Device �ɹ�"/*"\t  ���γ��Դ���(���10):" << times <<*/ "\t  ��������ʱ��(ms):" << timeGetTime() - startTime << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif
	}
	else {
		//Reset�豸ʧ��
		#ifdef DEBUG_CONSOLE
		SetConsoleAtt(FORE_RED + FORE_LIGHT);
		cout << "Reset Device ʧ��\t" << hr2 << endl;
		SetConsoleAtt(FORE_WHITE);
		#endif

		int res = MessageBox(nullptr, TEXT("�����豸ʧ��\n\n����? (ȡ������˳�)"), TEXT("����"), MB_OKCANCEL);
		if (res == 1) {
			goto retry;
		}
		else {
			SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
	}
}