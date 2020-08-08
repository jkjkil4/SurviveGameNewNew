#pragma once

#include "Room.h"

#include "../Game/Save.h"

namespace My {
	class Room_CreateSave;
}


class My::Room_CreateSave : public Room
{
public:
	Room_CreateSave(const std::wstring& save);
	~Room_CreateSave() override = default;

	void onLogic() override;

	void onDestroy() override;

	void threadCreateSave();

	std::thread* thCreate;

	std::wstring saveName;
};