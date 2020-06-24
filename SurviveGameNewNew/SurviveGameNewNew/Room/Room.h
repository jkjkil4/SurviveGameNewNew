#pragma once

namespace My {
	class Room;
}

class My::Room 
{
public:
	virtual ~Room() = default;

	virtual void onLogic();
	virtual void onRender();

	virtual void onDestroy();


	virtual void mouseEvent();

	virtual void wheelEvent();

private:

};