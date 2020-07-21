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

	void test(AbstractButton* btn) { std::cout << "��ť " << btn << " ������" << std::endl; }
};