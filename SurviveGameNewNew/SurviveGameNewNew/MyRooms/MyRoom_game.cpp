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
	MyTexture* textureBtnBig = &e->data.guiTexture.btnBig;

	//Esc菜单
	{
		MyPushButton* btnBack = new MyPushButton(e, textureBtnBig->g_pTexture, &textureBtnBig->info, e->g_pFont);
		btnBack->expr.setExpr(MyExpr::Expr{ MyExpr::Equal, MyExpr::And, 10000 });
		btnBack->pVisible = &visibleFlags;
		btnBack->text = TEXT("保存并返回至标题界面");
		btnBack->setPressSlot(PUSH_BUTTON_SLOT(&MyRoom_game::btnBackPressed), this);
		widgets.push_back(btnBack);
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
	int viewX = player.x - e->getViewW() / 2;
	int viewY = player.y - e->getViewH() / 2;
	viewX = bound(0, viewX, roomWidth * 16 - e->getViewW());
	viewY = bound(0, viewY, roomHeight * 16 - e->getViewH());
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
	if (e->mouseX >= 0 && e->mouseY >= 0 && e->mouseX <= e->getViewW() && e->mouseY <= e->getViewH()) {
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
	int viewX = player.x - e->getViewW() / 2;
	int viewY = player.y - e->getViewH() / 2;
	viewX = bound(0, viewX, roomWidth * 16 - e->getViewW());
	viewY = bound(0, viewY, roomHeight * 16 - e->getViewH());
	//绘制方块
	int xMax = (viewX + e->getViewW()) / 16;
	int yMax = (viewY + e->getViewH()) / 16;
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
	string str = "visibleFlags: " + to_string(visibleFlags)
		+ "\n左右移动: A、D    跳跃: 空格键\n左键删除方块 右键放置方块\n"
		"\nFPS: " + to_string(*e->fps)
		+ "\n玩家坐标: " + to_string(player.x) + " , " + to_string(player.y)
		+ "\n玩家速度: " + to_string(player.currentXSpd) + " , " + to_string(player.currentYSpd)
		+ "\n玩家横向速度限制(可以按W来增加，按S来降低): " + to_string(player.xSpdMax)
		+ "\n跳跃次数: " + to_string(player.jumped) + "   最大跳跃次数: " + to_string(player.jumpMax)
		+ "\n\n提示: 按Esc打开菜单      仅在标题界面能关闭窗口";
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, 0, DT_LEFT | DT_TOP, D3DCOLOR_XRGB(0, 0, 0));
}

void MyRoom_game::_onDestroy() {

}

void MyRoom_game::btnBackPressed(MyMouseEvent ev) {
	if (ev.mouse == VK_LBUTTON) {
		save->playerState->x = player.x;
		save->playerState->y = player.y;
		e->global.saveSave = new MyGlobal::SaveSave(save);
		setChangeRoomStr("saveSave");
	}
}
