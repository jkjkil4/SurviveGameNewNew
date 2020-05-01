#ifndef _MYROOM_H
#define _MYROOM_H

#include "../MyEngine.h"

#include "../MyGame/MySave.h"

#include "../MyWidgets/MyWidget.h"

class MyRoom
{
private:
	std::string changeRoomStr = "";

public:
	explicit MyRoom(MyEngine* e);
	virtual ~MyRoom() = default;
	
	NEEDLOCK_VARIBLE_FUNC(ChangeRoomStr, changeRoomStr, std::string);

	void onBeforeKeyCheck();

	void onLogic();
	virtual void _onLogic(){}
	void onRender();
	virtual void _onRender(){}
	void onDebug();
	virtual void _onDebug(){}

	void onResize();
	virtual void _onResize(){}

	void onDestroy();
	virtual void _onDestroy(){}

	MyEngine* e = nullptr;

	int visibleFlags = 0;
	bool canClose = false;

	std::vector<MyWidget*> widgets;

	MyWidget* focusWidget = nullptr;
	MyWidget* mouseWidget = nullptr;

	int sendMessage = 0;
};

#endif //_MYROOM_H