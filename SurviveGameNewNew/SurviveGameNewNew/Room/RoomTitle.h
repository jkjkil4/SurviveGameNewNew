#pragma once

#include "Room.h"

namespace My {
	class Room_Title;
}


class My::Room_Title : public Room
{
public:
	Room_Title();
	~Room_Title() override = default;

	void onLogic() override;

	void onRender() override;

	void test(AbstractButton* btn) { std::cout << "按钮 " << btn << " 被按下" << std::endl; }
};