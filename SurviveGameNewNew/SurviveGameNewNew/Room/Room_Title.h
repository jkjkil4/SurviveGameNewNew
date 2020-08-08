#pragma once

#include "Room.h"

#include "../Class/OperationClass.h"

#include "../Widget/ImageLabel/ImageLabel.h"
#include "../Widget/TextLabel/TextLabel.h"
#include "../Widget/Button/Button.h"
#include "../Widget/LineEdit/LineEdit.h"

#include "../Game/Save.h"

namespace My {
	class Room_Title;
}


class My::Room_Title : public Room
{
public:
	enum VisibleFlags { 
		VF_Title, 
		VF_SaveSelect, VF_SaveCreate, VF_SaveRename,
		VF_Multiplayer,
		VF_Settings
	};

	Room_Title(int visibleNum_);
	~Room_Title() override = default;

	void onLogic() override;

	void onRender() override;

	void onDestroy() override;

	void setVisibleNum(int num) override;

	bool isSaveNameRight(const std::wstring& name);

	void onBtnSigleplayerClicked(AbstractButton*) { setVisibleNum(VF_SaveSelect); }
	void onBtnMultiplayerClicked(AbstractButton*) { setVisibleNum(VF_Multiplayer); }
	void onBtnSettingsClicked(AbstractButton*) { setVisibleNum(VF_Settings); }
	void onBtnExitClicked(AbstractButton*) { throw RoomGoto(nullptr); }

	void onBtnBackClicked(AbstractButton*) { setVisibleNum(VF_Title); }
	void onBtnCreateClicked(AbstractButton*) { setVisibleNum(VF_SaveCreate); }
	void onBtnCreateAcceptClicked(AbstractButton*);
	void onBtnSigleplayerJoinClicked(AbstractButton*) {  }
	void onBtnRenameClicked(AbstractButton*) { setVisibleNum(VF_SaveRename); }
	void onBtnRenameAcceptClicked(AbstractButton*);
	void onBtnSaveDeleteClicked(AbstractButton*) {  }
	void onBtnBackToSelectClicked(AbstractButton*) { setVisibleNum(VF_SaveSelect); }

	struct SelectSaveMenu
	{
		std::vector<SaveInfo*> savesInfo;
		Button* btnJoin, * btnRename, * btnDelete;
		LineEdit* saveNameEdit;
	}selectSaveMenu;
	
};