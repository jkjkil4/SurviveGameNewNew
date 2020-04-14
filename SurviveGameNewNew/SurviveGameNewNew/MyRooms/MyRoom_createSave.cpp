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
	th->detach();
}

void MyRoom_createSave::thFunc() {
	MySave save;
	//创建
	MySave::Info* info = new MySave::Info(saveName, time(nullptr), 0, seed, saveWidth, saveHeight);
	if (!save.create(info, &proc, &needUpdate)) {
		//如果创建失败
		MessageBox(nullptr, TEXT("创建失败"), TEXT("错误"), MB_OK);
		return;
	}
	flag = true;
	//写入
	if (!save.save(&proc, &needUpdate)) {
		//如果写入失败
		MessageBox(nullptr, TEXT("写入失败"), TEXT("错误"), MB_OK);
		return;
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
	safeDelete(th);
}
