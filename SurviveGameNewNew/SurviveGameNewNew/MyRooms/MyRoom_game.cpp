#include "MyRoom_game.h"

MyRoom_game::MyRoom_game(MyKey* key, MyMouse* mouse, MyVaribles* vars, MyData *data, int roomWidth, int roomHeight) 
	: MyRoom(key, mouse, vars, data) 
{
	//初始化玩家的精灵指针
	D3DXCreateSprite(vars->g_pDevice, &g_pSpritePlayer);
	//初始化字体
	D3DXCreateFont(vars->g_pDevice, 20, 10, 0, 1000, FALSE, DEFAULT_CHARSET, 0, 0, 0, NULL, &g_pFont);
	//其他操作
	this->roomWidth = roomWidth;
	this->roomHeight = roomHeight;
	this->blockCount = roomWidth * roomHeight;
	blocks = new int[blockCount];
	//填充
	for (int j = 0; j < roomHeight; j++) {
		for (int i = 0; i < roomWidth; i++) {
			if ( j > 15 && (i == j || i == 2 * j || i == 3 * j || i == 4 * j || i == 5 * j || i == 6 * j)) {
				setBlockBy2d(i, j, 1);
			} else {
				setBlockBy2d(i, j, 0);
			}
		}
	}
	for (int i = 0; i < roomWidth; i+=5) {
		setBlockBy2d(i, 16, 3);
	}
	setBlockBy2d(roomWidth - 1, roomHeight - 1, 3);
	player.x = 100;
	player.y = 100;

	//fps
	startGetFps = timeGetTime();
}

int MyRoom_game::findBlockBy2d(int x, int y) {
	return (x >= 0 && y >= 0 && x < roomWidth && y < roomHeight ? blocks[x + roomWidth * y] : -1);
}
void MyRoom_game::setBlockBy2d(int x, int y, int id) {
	if (x >= 0 && y >= 0 && x < roomWidth && y < roomHeight) {
		blocks[x + roomWidth * y] = id;
	}
}


int MyRoom_game::onLogic() {
	//得到逻辑处理开始的时间
	//while (isOnRender)
	//	Sleep(1);
	//isOnLogic = true;
	int timeStart = timeGetTime();
	//得到视野坐标
	int viewX = player.x - vars->viewW / 2;
	int viewY = player.y - vars->viewH / 2;
	viewX = bound(0, viewX, roomWidth * 16 - vars->viewW);
	viewY = bound(0, viewY, roomHeight * 16 - vars->viewH);
	//得到鼠标所在方块坐标
	int blockX = (mouse->x + viewX) / 16;
	int blockY = (mouse->y + viewY) / 16;
	//更新玩家位置
	player.updatePos(blocks, roomWidth, roomHeight, key);
	//加速
	if (key->w) {
		player.xSpdMax += 1;
	}
	if (key->s) {
		player.xSpdMax -= 1;
		if (player.xSpdMax < 3) {
			player.xSpdMax = 3;
		}
	}
	//计算fps
	fpsCount++;
	if (timeGetTime() - startGetFps > 500) {
		fps = fpsCount * 2;
		startGetFps = timeGetTime();
		fpsCount = 0;
	}
	//放置方块
	if (mouse->x >= 0 && mouse->y >= 0 && mouse->x <= vars->viewW && mouse->y <= vars->viewH) {
		if (mouse->right) {
			setBlockBy2d(blockX, blockY, 1);
		}
		else if (mouse->left) {
			setBlockBy2d(blockX, blockY, 0);
		}
	}
	//返回逻辑处理消耗的时间
	//isOnLogic = false;
	return timeGetTime() - timeStart;
}

int MyRoom_game::onRender() {
	//得到渲染开始的时间
	//while (isOnLogic)
	//	Sleep(1);
	//isOnRender = true;
	int timeStart = timeGetTime();
	//一些操作
	int viewX = player.x - vars->viewW / 2;
	int viewY = player.y - vars->viewH / 2;
	viewX = bound(0, viewX, roomWidth * 16 - vars->viewW);
	viewY = bound(0, viewY, roomHeight * 16 - vars->viewH);
	//渲染
	IDirect3DSurface9* g_pOldRenderTarget;
	vars->g_pDevice->GetRenderTarget(0, &g_pOldRenderTarget);
	vars->g_pDevice->SetRenderTarget(0, vars->g_pRenderSurface);
	vars->g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	//开始绘制
	vars->g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//绘制方块
	int xMax = (viewX + vars->viewW) / 16;
	int yMax = (viewY + vars->viewH) / 16;
	int xStart = viewX / 16;
	int yStart = viewY / 16;
	D3DXVECTOR3* off = &D3DXVECTOR3((float)(viewX % 16), (float)(viewY % 16), 0);
	for (int j = yStart; j < roomHeight && j <= yMax; j++) {
		for (int i = xStart; i < roomWidth && i <= xMax; i++) {
			int id = findBlockBy2d(i, j);
			if (id > 0) {
				vars->g_pSprite->Draw(data->origBlocksTextureData->texture(id), nullptr, 
					off, &D3DXVECTOR3((i-xStart)*16.0f, (j-yStart)*16.0f, 0), 0xffffffff);
			}
		}
	}
	//结束绘制
	vars->g_pSprite->End();
	//绘制玩家
	mySetScale(g_pSpritePlayer, (float)(player.x - viewX), (float)(player.y - MyPlayer::plH/2 - viewY),
		(float)(player.direction), 1.0f);
	g_pSpritePlayer->Begin(D3DXSPRITE_ALPHABLEND);
	g_pSpritePlayer->Draw(data->g_pTexturePlayer, nullptr, &D3DXVECTOR3((float)(MyPlayer::plW / 2 + viewX), (float)(MyPlayer::plH + viewY), 0),
		&D3DXVECTOR3((float)player.x, (float)player.y, 0), 0xffffffff);
	g_pSpritePlayer->End();
#if MyDebug
	//绘制DEBUG
	vars->g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	onDebug();
	vars->g_pSprite->End();
#endif
	// 绘制纹理
	vars->g_pDevice->SetRenderTarget(0, g_pOldRenderTarget);
	//g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 204, 255), 1.0f, 0);
	vars->g_pDevice->BeginScene();		//获取绘制权限
	vars->g_pSpriteRender->Begin(NULL);
	vars->g_pSpriteRender->Draw(vars->g_pRenderTexture, nullptr, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
	vars->g_pSpriteRender->End();
	vars->g_pDevice->EndScene();		//结束绘制
	vars->g_pDevice->Present(nullptr, nullptr, 0, nullptr);	//前后台缓冲区交换的"源动力"
	//返回渲染消耗的时间
	//isOnRender = false;
	return timeGetTime() - timeStart;
}

void MyRoom_game::onDestroy() {
	Safe_Release(g_pSpritePlayer);
	Safe_Release(g_pFont);
}

#if MyDebug
void MyRoom_game::onDebug(){
	using namespace std;
	string str = "左右移动: A、D    跳跃: 空格键\n左键删除方块 右键放置方块\n"
		  "\nFPS: " + to_string(fps)
		+ "\n玩家坐标: " + to_string(player.x) + " , " + to_string(player.y)
		+ "\n玩家速度: " + to_string(player.currentXSpd) + " , " + to_string(player.currentYSpd)
		+ "\n玩家横向速度限制(可以按W来增加，按S来降低): " + to_string(player.xSpdMax)
		+ "\n跳跃次数: " + to_string(player.jumped) + "   最大跳跃次数: " + to_string(player.jumpMax);
	g_pFont->DrawText(NULL, stringToWstring(str).c_str(), -1, NULL, DT_LEFT | DT_TOP, D3DCOLOR_XRGB(0, 0, 0));
}
#endif
