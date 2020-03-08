#include "MyRoom_game.h"

void MyRoom_game::onInit() {

}

int MyRoom_game::onLogic() {
	//得到逻辑处理开始的时间
	int timeStart = timeGetTime();

	//返回逻辑处理消耗的时间
	return timeGetTime() - timeStart;
}

int MyRoom_game::onRender() {
	//得到渲染开始的时间
	int timeStart = timeGetTime();

	//返回渲染消耗的时间
	return timeGetTime() - timeStart;
}

void MyRoom_game::onDestroy() {

}
