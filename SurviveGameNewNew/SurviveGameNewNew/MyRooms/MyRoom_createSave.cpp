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
	//����
	MySave::Info* info = new MySave::Info(saveName, time(nullptr), 0, seed, saveWidth, saveHeight);
	if (!save.create(info, &proc, &needUpdate)) {
		//�������ʧ��
		MessageBox(nullptr, TEXT("����ʧ��"), TEXT("����"), MB_OK);
		return;
	}
	flag = true;
	//д��
	if (!save.save(&proc, &needUpdate)) {
		//���д��ʧ��
		MessageBox(nullptr, TEXT("д��ʧ��"), TEXT("����"), MB_OK);
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
	string type = (flag ? "д���ļ�" : "��������");
	string str = "��ǰ���е���: " + type
		+ "\n���: " + to_string(saveWidth) + "    �߶�: " + to_string(saveHeight)
		+ "\n����: " + to_string((int)((proc / (double)saveCount * 100))) + "%";
	wstring wstr = stringToWstring(str);
	e->g_pFont->DrawText(e->g_pSprite, wstr.c_str(), -1, &rect(0, 0, e->viewW, e->viewH), DT_CENTER | DT_VCENTER, 0xff000000);
}

void MyRoom_createSave::_onDebug() {}

void MyRoom_createSave::_onDestroy() {
	safeDelete(th);
}
