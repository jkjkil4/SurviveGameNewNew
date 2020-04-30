#include "MyRoom_game.h"

using namespace std;

MyRoom_game::MyRoom_game(MyEngine* e) : MyRoom(e) {
	//初始化
	e->global.game->getVarible(save);
	roomWidth = save->info->width;
	roomHeight = save->info->height;
	blockCount = roomWidth * roomHeight;
	blocks = save->blocks->blocks;
	player.x = save->playerState->x;
	player.y = save->playerState->y;

	//窗口控件
	{
		solidColorWidget = new MySolidColorWidget(e, e->viewW, e->viewH);
		solidColorWidget->pVisible = &visibleFlags;
		solidColorWidget->visible = 9999;	//这行和下一行设置了当visible大于9999时显示
		solidColorWidget->expr.setExpr(MyExpr::Expr{ MyExpr::More, MyExpr::And });
		solidColorWidget->color = D3DCOLOR_ARGB(96, 0, 0, 0);
		widgets.push_back(solidColorWidget);
	}

	//重置
	e->global.reset();
}

int MyRoom_game::findBlockBy2d(int x, int y) {
	return (x >= 0 && y >= 0 && x < roomWidth && y < roomHeight ? blocks[x + roomWidth * y] : -1);
}
void MyRoom_game::setBlockBy2d(int x, int y, int id) {
	if (x >= 0 && y >= 0 && x < roomWidth && y < roomHeight)
		blocks[x + roomWidth * y] = id;
}

void MyRoom_game::_onLogic() {
	if (e->keyPressFlag(VK_ESCAPE)) {	//如果Esc键被按下
		if (visibleFlags > 9999) {	//如果visibleFlags大于9999 (显示了Esc菜单)
			//关闭Esc菜单
			visibleFlags = 0;
		}
		else {
			//开启Esc菜单
			visibleFlags = 10000;
		}
	}

	//得到视野坐标
	int viewX = player.x - e->viewW / 2;
	int viewY = player.y - e->viewH / 2;
	viewX = bound(0, viewX, roomWidth * 16 - e->viewW);
	viewY = bound(0, viewY, roomHeight * 16 - e->viewH);
	//得到鼠标所在方块坐标
	int blockX = (e->mouseX + viewX) / 16;
	int blockY = (e->mouseY + viewY) / 16;
	//更新玩家位置
	player.updatePos(blocks, roomWidth, roomHeight, e);
	//加速
	if (e->keyFlag('W')) {
		player.xSpdMax += 1;
	}
	if (e->keyFlag('S')) {
		player.xSpdMax -= 1;
		if (player.xSpdMax < 3) {
			player.xSpdMax = 3;
		}
	}
	//放置方块
	if (e->mouseX >= 0 && e->mouseY >= 0 && e->mouseX <= e->viewW && e->mouseY <= e->viewH) {
		if (e->keyFlag(VK_RBUTTON)) {
			if (16 * (blockX + 1) <= player.x - player.plW / 2 || 16 * blockX >= player.x + player.plW / 2
				|| 16 * (blockY + 1) <= player.y - player.plH || 16 * blockY >= player.y) {
				setBlockBy2d(blockX, blockY, 1);
			}
		}
		else if (e->keyFlag(VK_LBUTTON)) {
			setBlockBy2d(blockX, blockY, 0);
		}
	}
}
void MyRoom_game::_onRender() {
	//一些操作
	int viewX = player.x - e->viewW / 2;
	int viewY = player.y - e->viewH / 2;
	viewX = bound(0, viewX, roomWidth * 16 - e->viewW);
	viewY = bound(0, viewY, roomHeight * 16 - e->viewH);
	//绘制方块
	int xMax = (viewX + e->viewW) / 16;
	int yMax = (viewY + e->viewH) / 16;
	int xStart = viewX / 16;
	int yStart = viewY / 16;
	D3DXVECTOR3* off = &D3DXVECTOR3((float)(viewX % 16), (float)(viewY % 16), 0);
	for (int j = yStart; j < roomHeight && j <= yMax; j++) {
		for (int i = xStart; i < roomWidth && i <= xMax; i++) {
			int id = findBlockBy2d(i, j);
			if (id > 0) {
				e->g_pSprite->Draw(e->data.blockTexture.texture(id), nullptr,
					off, &D3DXVECTOR3((i - xStart) * 16.0f, (j - yStart) * 16.0f, 0), 0xffffffff);
			}
		}
	}
	//绘制玩家
	mySetScale(e->g_pSprite, (float)(player.x - viewX), (float)(player.y - MyPlayer::plH / 2 - viewY),
		(float)(player.direction), 1.0f);
	e->g_pSprite->Draw(e->data.playerTexture.g_pPlayer, nullptr, &D3DXVECTOR3((float)(MyPlayer::plW / 2 + viewX), (float)(MyPlayer::plH + viewY), 0),
		&D3DXVECTOR3((float)player.x, (float)player.y, 0), 0xffffffff);
	mySetScale(e->g_pSprite, 0, 0, 1, 1);
}
void MyRoom_game::_onDebug() {
	string str = "左右移动: A、D    跳跃: 空格键\n左键删除方块 右键放置方块\n"
		"\nFPS: " + to_string(*e->fps)
		+ "\n玩家坐标: " + to_string(player.x) + " , " + to_string(player.y)
		+ "\n玩家速度: " + to_string(player.currentXSpd) + " , " + to_string(player.currentYSpd)
		+ "\n玩家横向速度限制(可以按W来增加，按S来降低): " + to_string(player.xSpdMax)
		+ "\n跳跃次数: " + to_string(player.jumped) + "   最大跳跃次数: " + to_string(player.jumpMax);
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, 0, DT_LEFT | DT_TOP, D3DCOLOR_XRGB(0, 0, 0));
}

void MyRoom_game::_onResize() {
	solidColorWidget->resize(e->viewW, e->viewH);
}

void MyRoom_game::_onDestroy() {
	safeDeleteArray(blocks);
}