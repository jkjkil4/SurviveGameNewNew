#include "MyRoom_createSave.h"

using namespace std;

MyRoom_createSave::MyRoom_createSave(MyEngine* e) : MyRoom(e) {
	e->global.createSave->getVarible(saveName, saveWidth, saveHeight, seed);
	saveCount = saveWidth * saveHeight;
	e->global.reset();
	th->detach();
}

void MyRoom_createSave::thFunc() {
	myd("正在创建存档" << endl);
	MySave save;
	//创建
	MySave::Info* info = new MySave::Info(saveName, saveName, time(nullptr), 0, seed, saveWidth, saveHeight);
	if (!save.create(info, &proc, &needUpdate, &m)) {
		//如果创建失败
		MessageBox(nullptr, TEXT("创建失败"), TEXT("错误"), MB_OK);
	}
	else {
		save.checkFileName();
		flag = true;
		//写入
		if (!save.save(&proc, &needUpdate, &m)) {
			//如果写入失败
			MessageBox(nullptr, TEXT("写入失败"), TEXT("错误"), MB_OK);
		}
	}
	myd("创建存档结束" << endl);
	MyGlobal* global = &e->global;
	global->visibleFlag = 1;
	setChangeRoomStr("title");
}

void MyRoom_createSave::_onLogic() {
	Mutex(m);
	needUpdate = true;
}

void MyRoom_createSave::_onRender() {
	m.lock();
	int _proc = proc;
	m.unlock();
	wstring type = (flag ? TEXT("写入文件") : TEXT("生成世界"));
	wstring wstr = TEXT("当前进行的是: ") + type
		+ TEXT("\n宽度: ") + to_wstring(saveWidth) + TEXT("    高度: ") + to_wstring(saveHeight)
		+ TEXT("\n进度: ") + to_wstring((int)((_proc / (double)saveCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_createSave::_onDestroy() {
	safeDelete(th);
}
