#pragma once

#include "Room.h"

namespace My {
	class RoomTitle;
}


class My::RoomTitle : public Room
{
public:
	~RoomTitle() override = default;

	void onLogic() override;

	void onRender() override;
};