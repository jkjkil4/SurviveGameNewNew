#include "MyRoom_saveSave.h"

using namespace std;

MyRoom_saveSave::MyRoom_saveSave(MyEngine* e) : MyRoom(e)
{
	e->global.saveSave->getVarible(save);
	e->global.reset();
	blockCount = save->info->width * save->info->height;
	th->detach();
}

void MyRoom_saveSave::thFunc() {
	myd("正在保存存档" << endl);
	if (!save->save(&proc, &needUpdate, &m)) {
		MessageBox(nullptr, TEXT("存档保存失败"), TEXT("错误"), MB_OK);
	}
	myd("保存存档结束" << endl);
	safeDelete(save);
	setChangeRoomStr("title");
}

void MyRoom_saveSave::_onLogic() {
	Mutex(m);
	needUpdate = true;
}

void MyRoom_saveSave::_onRender() {
	m.lock();
	int _proc = proc;
	m.unlock();
	wstring wstr = TEXT("正在保存\n") + to_wstring((int)((_proc / (double)blockCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_saveSave::_onDestroy() {
	safeDelete(th);
}

