#ifndef _MYROOM_H
#define _MYROOM_H

#include "../MyEngine.h"
#include "../MyWidgets/MyWidget.h"
#include "../MyWidgets/MyPushButton.h"

class MyRoom
{
public:
	explicit MyRoom(MyEngine* e);
	virtual ~MyRoom() = 0;
	
	void onLogic();
	virtual void _onLogic() = 0;
	void onRender();
	virtual void _onRender() = 0;
	void onDebug();
	virtual void _onDebug() = 0;

	void onDestroy();
	virtual void _onDestroy() = 0;

	MyEngine* e = nullptr;

	std::vector<MyWidget*> widgets;
};

#endif //_MYROOM_H