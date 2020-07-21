#pragma once

#include "Room.h"

#include "../Class/OperationClass.h"

namespace My {
	class Room_Title;
}


class My::Room_Title : public Room
{
public:
	enum VisibleFlags { 
		VF_Title, 
		VF_SaveSelect, VF_SaveCreate,
		VF_Multiplayer,
		VF_Settings
	};

	Room_Title();
	~Room_Title() override = default;

	void onLogic() override;

	void onRender() override;

	void onBtnSigleplayerClicked(AbstractButton*) { setVisibleNum(VF_SaveSelect); }
	void onBtnMultiplayerClicked(AbstractButton*) { setVisibleNum(VF_Multiplayer); }
	void onBtnSettingsClicked(AbstractButton*) { setVisibleNum(VF_Settings); }
	void onBtnExitClicked(AbstractButton*) { throw RoomGoto(nullptr); }

	void onBtnBackClicked(AbstractButton*) { setVisibleNum(VF_Title); }

	
};