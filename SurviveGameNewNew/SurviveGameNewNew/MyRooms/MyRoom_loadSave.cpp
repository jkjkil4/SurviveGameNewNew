#include "MyRoom_loadSave.h"

using namespace std;

MyRoom_loadSave::MyRoom_loadSave(MyEngine* e) : MyRoom(e) {
	e->global.loadSave->getVarible(path, fileName);
	e->global.reset();
	th->detach();
}

void MyRoom_loadSave::thFunc() {
	myd("���ڶ�ȡ�浵" << endl);
	MySave* save = new MySave;
	//��ȡ�浵
	if (!save->load(path, fileName, &proc, &needUpdate, &m)) {
		//��ȡʧ��
		myd("��ȡ�浵ʧ��");
		MessageBox(nullptr, TEXT("��ȡʧ��"), TEXT("����"), MB_OK);
		safeDelete(save);
		e->global.visibleFlag = 1;
		setChangeRoomStr("title");
		return;
	}
	myd("��ȡ�浵�ɹ�" << endl);
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
	wstring wstr = TEXT("���ڶ�ȡ\n") + to_wstring((int)((_proc / (double)blockCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_loadSave::_onDebug() {

}

void MyRoom_loadSave::_onDestroy() {
	safeDelete(th);
}
