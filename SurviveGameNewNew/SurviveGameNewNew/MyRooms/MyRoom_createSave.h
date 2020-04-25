#ifndef _MYROOM_CREATESAVE_H
#define _MYROOM_CREATESAVE_H

#include "MyRoom.h"

class MyRoom_createSave : public MyRoom
{
public:
	explicit MyRoom_createSave(MyEngine* e);
	~MyRoom_createSave() override = default;

	void _onLogic() override;
	void _onRender() override;

	void _onDestroy() override;

	std::wstring saveName = TEXT("NULL");
	int saveWidth = 400;
	int saveHeight = 400;
	UINT saveCount = 160000;
	UINT seed = 114514;

	bool needUpdate = false;
	UINT proc = 0;

	void thFunc();
	std::thread* th = new std::thread(&MyRoom_createSave::thFunc, this);
	bool flag = false;


};

#endif