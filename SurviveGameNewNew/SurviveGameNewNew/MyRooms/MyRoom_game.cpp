#include "MyRoom_game.h"

void MyRoom_game::onInit() {

}

int MyRoom_game::onLogic() {
	//�õ��߼�����ʼ��ʱ��
	int timeStart = timeGetTime();

	//�����߼��������ĵ�ʱ��
	return timeGetTime() - timeStart;
}

int MyRoom_game::onRender() {
	//�õ���Ⱦ��ʼ��ʱ��
	int timeStart = timeGetTime();

	//������Ⱦ���ĵ�ʱ��
	return timeGetTime() - timeStart;
}

void MyRoom_game::onDestroy() {

}
