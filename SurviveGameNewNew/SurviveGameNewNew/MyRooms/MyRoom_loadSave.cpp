#include "MyRoom_loadSave.h"

using namespace std;

MyRoom_loadSave::MyRoom_loadSave(MyEngine* e) : MyRoom(e) {
	e->global.loadSave->getVarible(path);
	e->global.reset();

	th->detach();
}

void MyRoom_loadSave::thFunc() {
	MySave* save = new MySave;
	//¶ÁÈ¡´æµµ
	if (!save->load(path, &proc, &needUpdate, &m)) {
		//¶ÁÈ¡Ê§°Ü
		MessageBox(nullptr, TEXT("¶ÁÈ¡Ê§°Ü"), TEXT("´íÎó"), MB_OK);
		safeDelete(save);
		e->global.visibleFlag = 1;
		setChangeRoomStr("title");
		return;
	}
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
	wstring wstr = TEXT("ÕýÔÚ¶ÁÈ¡\n") + to_wstring((int)((_proc / (double)blockCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_loadSave::_onDebug() {

}

void MyRoom_loadSave::_onDestroy() {
	safeDelete(th);
}
