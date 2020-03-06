#include "MyRoom_title.h"


void MyRoom_title::onInit(){
	//字体
	D3DXCreateFont(g_pDevice, 40, 20, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFont);
}
int MyRoom_title::onLogic(){
	//得到逻辑处理开始的时间
	int startTime = timeGetTime();
	//逻辑处理
	t++;
	//返回逻辑处理结束的时间
	return timeGetTime() - startTime;
}

int MyRoom_title::onRender(){
	//得到绘制开始的时间
	int startTime = timeGetTime();
	// 渲染到纹理
	IDirect3DSurface9* g_pOldRenderTarget;
	g_pDevice->GetRenderTarget(0, &g_pOldRenderTarget);
	g_pDevice->SetRenderTarget(0, g_pRenderSurface);
	g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g_pSprite->Draw(
		g_pTexture,				//绘制哪张图片		
		nullptr,	//绘制图片的哪个部分
		&D3DXVECTOR3(0, 0, 0),	//图片的锚点
		&D3DXVECTOR3(0, 0, 0),	//绘制在客户区的哪个位置
		D3DCOLOR_XRGB((int)(cos(t * PI / 180) * 127 + 127), (int)(sin(t * PI / 180) * 127 + 127), 255)//绘制混合色
	);
	g_pSprite->End();
	//绘制文字
	std::string text = "TESTTEXT 这是一段测试文字\naasdsdsd";
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 608;
	g_pFont->DrawText(NULL, stringToWstring(text).c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xffffffff);
	// 绘制纹理
	g_pDevice->SetRenderTarget(0, g_pOldRenderTarget);
	//g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	g_pDevice->BeginScene();		//获取绘制权限
	g_pSpriteRender->Begin(NULL);
	g_pSpriteRender->Draw(g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0),   //绘制函数
		&D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	g_pSpriteRender->End();
	g_pDevice->EndScene();		//结束绘制
	g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	//返回绘制结束的时间
	return timeGetTime() - startTime;
}

void MyRoom_title::onDestroy(){
	Safe_Release(g_pFont);
	delete this;
}
