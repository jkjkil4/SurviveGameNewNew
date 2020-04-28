#ifndef _MYROOM_H
#define _MYROOM_H

#include "../MyEngine.h"

#include "../MyGame/MySave.h"

#include "../MyWidgets/MyWidget.h"

class MyRoom
{
public:
	explicit MyRoom(MyEngine* e);
	virtual ~MyRoom() = default;
	
	void onBeforeKeyCheck();

	void onLogic();
	virtual void _onLogic(){}
	void onRender();
	virtual void _onRender(){}
	void onDebug();
	virtual void _onDebug(){}

	void onDestroy();
	virtual void _onDestroy(){}

	MyEngine* e = nullptr;

	int visibleFlags = 0;

	std::vector<MyWidget*> widgets;

	MyWidget* focusWidget = nullptr;
	MyWidget* mouseWidget = nullptr;

	std::string changeRoomStr = "";
	int sendMessage = 0;
};

#endif //_MYROOM_H