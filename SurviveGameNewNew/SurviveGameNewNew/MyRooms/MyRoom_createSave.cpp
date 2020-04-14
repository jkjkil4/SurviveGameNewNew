#include "MyRoom_createSave.h"

using namespace std;

MyRoom_createSave::MyRoom_createSave(MyEngine* e) : MyRoom(e) {
	MyGlobal* global = &e->global;
	saveName = global->createSaveName;
	saveWidth = global->createSaveWidth;
	saveHeight = global->createSaveHeight;
	saveCount = saveWidth * saveHeight;
	seed = global->createSaveSeed;
	global->resetCreateSave();
	blocks = new short[saveCount];
	th->detach();
}

int MyRoom_createSave::findBlockBy2d(int x, int y) {
	return (x >= 0 && y >= 0 && x < saveWidth&& y < saveHeight ? blocks[x + saveWidth * y] : -1);
}
void MyRoom_createSave::setBlockBy2d(int x, int y, int id) {
	if (x >= 0 && y >= 0 && x < saveWidth && y < saveHeight)
		blocks[x + saveWidth * y] = id;
}

void MyRoom_createSave::thFunc() {
	//生成世界
	{
		//填充
		for (int j = 0; j < saveHeight; j++) {
			for (int i = 0; i < saveWidth; i++) {
				if (j > 15 && (i == j || i == 2 * j || i == 3 * j || i == 4 * j || i == 5 * j || i == 6 * j)) {
					setBlockBy2d(i, j, 1);
				}
				else {
					setBlockBy2d(i, j, 0);
				}
				if (needUpdate)
					proc = i + j * saveWidth;
			}
		}
		for (int i = 0; i < saveWidth; i += 5) {
			setBlockBy2d(i, 16, 3);
		}
		setBlockBy2d(saveWidth - 1, saveHeight - 1, 3);
	}
	flag = true;
	//写入文件
	{
		wstring path = TEXT("data\\saves\\") + saveName;
		//检测是否已经存在
		bool dirFlag = true;
		while (dirFlag) {
			struct stat buffer;
			dirFlag = stat(wstringToString(path).c_str(), &buffer) == 0;
			
			if (!dirFlag)
				break;
			path += TEXT("_");
		}
		////创建文件夹
		CreateDirectory(TEXT("data"), nullptr);
		CreateDirectory(TEXT("data\\saves"), nullptr);
		CreateDirectory(path.c_str(), nullptr);
		CreateDirectory((path + TEXT("\\world")).c_str(), nullptr);
		proc = 0;
		//存档
		{
			ofstream out(path + TEXT("\\saveInfo"), ios::out | ios::binary);
			if (out.fail()) {
				MessageBox(nullptr, (TEXT("写入存档 ") + saveName + TEXT(" 失败(#1)")).c_str(), TEXT("错误"), MB_OK);
			}
			else {
				string saveNameStr = wstringToString(saveName);
				out.write((char*)saveNameStr.c_str(), saveNameStr.size());	//名称
				out.write((char*)&seed, 2);			//种子
				out.write((char*)&saveWidth, 2);	//横向方块数量
				out.write((char*)&saveHeight, 2);	//纵向方块数量
				out.close();
			}
		}
		//玩家
		{
			int playerX = 1020, playerY = 100;
			ofstream out(path + TEXT("\\player"), ios::out | ios::binary);
			if (out.fail()) {
				MessageBox(nullptr, (TEXT("写入存档 ") + saveName + TEXT(" 失败(#2)")).c_str(), TEXT("错误"), MB_OK);
			}
			else {
				out.write((char*)&playerX, 2);	//玩家横坐标
				out.write((char*)&playerY, 2);	//玩家纵坐标
				out.close();
			}
		}
		//方块
		{
			ofstream out(path + TEXT("\\world\\blocks"), ios::out | ios::binary);
			if (out.fail()) {
				MessageBox(nullptr, (TEXT("写入存档 ") + saveName + TEXT(" 失败(#3)")).c_str(), TEXT("错误"), MB_OK);
			}
			else {
				for (int i = 0; i < saveHeight; i++) {
					out.write((char*)(blocks + (i * saveWidth)), (streamsize)saveWidth * 2);
					if (needUpdate)
						proc = i * saveWidth;
				}
				out.close();
			}
		}
	}
	
	MyGlobal* global = &e->global;
	global->visibleFlag = 1;
	changeRoomStr = "title";
}

void MyRoom_createSave::_onLogic() {
	needUpdate = true;
}

void MyRoom_createSave::_onRender() {
	string type = (flag ? "写入文件" : "生成世界");
	string str = "当前进行的是: " + type
		+ "\n宽度: " + to_string(saveWidth) + "    高度: " + to_string(saveHeight)
		+ "\n进度: " + to_string((int)((proc / (double)saveCount * 100))) + "%";
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->viewW, e->viewH), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_createSave::_onDebug() {}

void MyRoom_createSave::_onDestroy() {
	safeDeleteArray(blocks);
	safeDelete(th);
}
