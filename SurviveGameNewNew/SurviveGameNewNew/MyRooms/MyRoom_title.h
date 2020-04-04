#pragma once
#include "MyRoom.h"

class MyRoom_title : public MyRoom
{
public:
	MyRoom_title(MyEngine* e);
	~MyRoom_title() override;

	void _onLogic() override;
	void _onRender() override;
	void _onDebug() override;
	void _onDestroy() override;

	void _btnSiglePressed(int mouse);
	void _btnMultiPressed(int mouse);
	void _btnSettingsPressed(int mouse);
	void _btnExitPressed(int mouse);

	MyEngine* e = nullptr;
};

