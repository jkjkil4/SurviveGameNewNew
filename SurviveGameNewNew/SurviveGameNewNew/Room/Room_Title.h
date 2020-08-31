#pragma once

#include "Room.h"

#include "../Class/OperationClass.h"

#include "../Widget/ImageLabel/ImageLabel.h"
#include "../Widget/TextLabel/TextLabel.h"
#include "../Widget/Button/Button.h"
#include "../Widget/LineEdit/LineEdit.h"
#include "../Widget/ListWidget/ListWidget.h"
#include "../Widget/MsgBox/MsgBox.h"

#include "../Widget/ListWidget/Item/SaveListItem.h"

#include "../Game/Save.h"

namespace My {
	class Room_Title;
}


class My::Room_Title : public Room
{
public:
	enum VisibleFlags { 
		VF_Title, 
		VF_SaveSelect, VF_SaveCreate, VF_SaveRename, VF_SaveDelete,
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

	void onBtnSingleplayerClicked(AbstractButton*) { setVisibleNum(VF_SaveSelect); }
	void onBtnMultiplayerClicked(AbstractButton*) { setVisibleNum(VF_Multiplayer); }
	void onBtnSettingsClicked(AbstractButton*) { setVisibleNum(VF_Settings); }
	void onBtnExitClicked(AbstractButton*) { throw RoomGoto(nullptr); }

	void onBtnBackClicked(AbstractButton*) { setVisibleNum(VF_Title); }
	void onBtnCreateClicked(AbstractButton*) { setVisibleNum(VF_SaveCreate); }
	void onBtnCreateAcceptClicked(AbstractButton*);
	void onBtnSingleplayerJoinClicked(AbstractButton*) {  }
	void onBtnRenameClicked(AbstractButton*);
	void onBtnRenameAcceptClicked(AbstractButton*);
	void onBtnSaveDeleteClicked(AbstractButton*);
	void onBtnSaveDeleteBack(int index);
	void onBtnBackToSelectClicked(AbstractButton*) { setVisibleNum(VF_SaveSelect); }

	void onSaveListClicked(ListWidgetItem* item);

	struct SelectSaveMenu
	{
		//std::vector<SaveInfo*> savesInfo;
		ListWidget* saveListWidget;
		Button* btnJoin, * btnRename, * btnDelete;
		LineEdit* saveNameEdit;

		TextLabel* oldSaveNameLabel;

		MsgBox* deleteSaveMsgBox;

		TextLabel* saveInfoWidget;
	}selectSaveMenu;
};