#ifndef _MYROOM_SAVESAVE_H
#define _MYROOM_SAVESAVE_H

#include "MyRoom.h"


class MyRoom_saveSave : public MyRoom
{
public:
	explicit MyRoom_saveSave(MyEngine* e);

	void thFunc();

	void _onLogic() override;
	void _onRender() override;

	void _onDestroy() override;

	MySave* save = nullptr;

	std::thread* th = new std::thread(&MyRoom_saveSave::thFunc, this);
	UINT proc = 0;
	UINT blockCount = 160000;
	bool needUpdate = false;
	std::mutex m;
};

#endif