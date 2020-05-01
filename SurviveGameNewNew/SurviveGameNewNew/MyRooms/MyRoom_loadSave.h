#ifndef _MYROOM_LOADSAVE_H
#define _MYROOM_LOADSAVE_H

#include "MyRoom.h"

class MyRoom_loadSave : public MyRoom
{
public:
	explicit MyRoom_loadSave(MyEngine* e);
	~MyRoom_loadSave() override = default;

	void thFunc();

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;

	void _onDestroy() override;

	std::wstring path = TEXT("");
	std::wstring fileName = TEXT("NULL");

	std::thread* th = new std::thread(&MyRoom_loadSave::thFunc, this);
	UINT proc = 0;
	bool needUpdate = false;
	UINT blockCount = 160000;
	std::mutex m;
};

#endif