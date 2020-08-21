#include "Room_CreateSave.h"

#include "Room_Title.h"

using namespace My;
using namespace std;

Room_CreateSave::Room_CreateSave(const wstring& save) {
	saveName = save;
	thCreate = new thread(&Room_CreateSave::threadCreateSave, this);
}

void Room_CreateSave::threadCreateSave() {
	Save save;
	save.create(saveName, rand() % 114514, 8000, 2000);
	save.save();
}

void Room_CreateSave::onLogic() {
	DWORD exitCode;
	GetExitCodeThread(thCreate->native_handle(), &exitCode);
	if (exitCode != STILL_ACTIVE) {
		throw RoomGoto(new Room_Title(Room_Title::VF_SaveSelect));
	}

	Room::onLogic();
}

void Room_CreateSave::onDestroy() {
	thCreate->join();
	delete thCreate;

	Room::onDestroy();
}