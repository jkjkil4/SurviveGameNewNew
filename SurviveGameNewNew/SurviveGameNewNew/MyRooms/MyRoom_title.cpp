#include "MyRoom_title.h"


void MyRoom_title::onInit(){
	//����
	D3DXCreateFont(g_pDevice, 40, 20, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFont);
}
int MyRoom_title::onLogic(){
	//�õ��߼�����ʼ��ʱ��
	int startTime = timeGetTime();
	//�߼�����
	t++;
	//�����߼����������ʱ��
	return timeGetTime() - startTime;
}

int MyRoom_title::onRender(){
	//�õ����ƿ�ʼ��ʱ��
	int startTime = timeGetTime();
	// ��Ⱦ������
	IDirect3DSurface9* g_pOldRenderTarget;
	g_pDevice->GetRenderTarget(0, &g_pOldRenderTarget);
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g_pSprite->Draw(
		g_pTexture,				//��������ͼƬ		
		nullptr,	//����ͼƬ���ĸ�����
		&D3DXVECTOR3(0, 0, 0),	//ͼƬ��ê��
		&D3DXVECTOR3(0, 0, 0),	//�����ڿͻ������ĸ�λ��
		D3DCOLOR_XRGB((int)(cos(t * PI / 180) * 127 + 127), (int)(sin(t * PI / 180) * 127 + 127), 255)//���ƻ��ɫ
	);
	g_pSprite->End();
	//��������
	std::string text = "TESTTEXT ����һ�β�������\naasdsdsd";
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 608;
	g_pFont->DrawText(NULL, stringToWstring(text).c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xffffffff);
	// ��������
	g_pDevice->SetRenderTarget(0, g_pOldRenderTarget);
	//g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	g_pDevice->BeginScene();		//��ȡ����Ȩ��
	g_pSpriteRender->Begin(NULL);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0),   //���ƺ���
		&D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//��������
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//ǰ��̨������������"Դ����"
	//���ػ��ƽ�����ʱ��
	return timeGetTime() - startTime;
}

void MyRoom_title::onDestroy(){
	Safe_Release(g_pFont);
	delete this;
}
