#ifndef _MYROOM_LOADSAVE_H
#define _MYROOM_LOADSAVE_H

#include "MyRoom.h"

class MyRoom_loadSave : public MyRoom
{
public:
	explicit MyRoom_loadSave(MyEngine* e);

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;

	void _onDestroy() override;
};

#endif