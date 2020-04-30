#include "MyRoom_loadSave.h"

MyRoom_loadSave::MyRoom_loadSave(MyEngine* e) : MyRoom(e) {
	e->global.loadSave->getVarible(saveName);
	e->global.reset();
}

void MyRoom_loadSave::_onLogic() {
	
}

void MyRoom_loadSave::_onRender() {

}

void MyRoom_loadSave::_onDebug() {

}

void MyRoom_loadSave::_onDestroy() {

}
