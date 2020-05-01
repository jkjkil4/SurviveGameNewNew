#include "MyRoom_createSave.h"

using namespace std;

MyRoom_createSave::MyRoom_createSave(MyEngine* e) : MyRoom(e) {
	e->global.createSave->getVarible(saveName, saveWidth, saveHeight, seed);
	saveCount = saveWidth * saveHeight;
	e->global.reset();
	th->detach();
}

void MyRoom_createSave::thFunc() {
	myd("���ڴ����浵" << endl);
	MySave save;
	//����
	MySave::Info* info = new MySave::Info(saveName, saveName, time(nullptr), 0, seed, saveWidth, saveHeight);
	if (!save.create(info, &proc, &needUpdate, &m)) {
		//�������ʧ��
		MessageBox(nullptr, TEXT("����ʧ��"), TEXT("����"), MB_OK);
	}
	else {
		save.checkFileName();
		flag = true;
		//д��
		if (!save.save(&proc, &needUpdate, &m)) {
			//���д��ʧ��
			MessageBox(nullptr, TEXT("д��ʧ��"), TEXT("����"), MB_OK);
		}
	}
	myd("�����浵����" << endl);
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
	wstring type = (flag ? TEXT("д���ļ�") : TEXT("��������"));
	wstring wstr = TEXT("��ǰ���е���: ") + type
		+ TEXT("\n���: ") + to_wstring(saveWidth) + TEXT("    �߶�: ") + to_wstring(saveHeight)
		+ TEXT("\n����: ") + to_wstring((int)((_proc / (double)saveCount * 100))) + TEXT("%");
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->getViewW(), e->getViewH()), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_createSave::_onDestroy() {
	safeDelete(th);
}
