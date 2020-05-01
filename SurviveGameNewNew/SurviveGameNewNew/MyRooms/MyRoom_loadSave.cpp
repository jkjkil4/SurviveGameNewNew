#include "MyRoom_loadSave.h"

using namespace std;

MyRoom_loadSave::MyRoom_loadSave(MyEngine* e) : MyRoom(e) {
	e->global.loadSave->getVarible(path, fileName);
	e->global.reset();
	th->detach();
}

void MyRoom_loadSave::thFunc() {
	myd("正在读取存档" << endl);
	MySave* save = new MySave;
	//读取存档
	if (!save->load(path, fileName, &proc, &needUpdate, &m)) {
		//读取失败
		myd("读取存档失败");
		MessageBox(nullptr, TEXT("读取失败"), TEXT("错误"), MB_OK);
		safeDelete(save);
		e->global.visibleFlag = 1;
		setChangeRoomStr("title");
		return;
	}
	myd("读取存档成功" << endl);
	e->global.game = new MyGlobal::Game(save);
	setChangeRoomStr("game");
}

void MyRoom_loadSave::_onLogic() {
	Mutex(m);
	needUpdate = true;
}

void MyRoom_loadSave::_onRender() {
	m.lock();
	int _proc = proc;
	m.unlock();
	wstring wstr = TEXT("正在读取\n") + to_wstring((int)((_proc / (double)blockCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_loadSave::_onDebug() {

}

void MyRoom_loadSave::_onDestroy() {
	safeDelete(th);
}
