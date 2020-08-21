#pragma once

#include "../Widget.h"

#include "ListWidgetItem.h"

namespace My {
	class ListWidget;
	typedef void(Object::* ListWidgetSlot)(ListWidgetItem*);
}

class My::ListWidget : public Widget
{
public:
	ListWidget(int w, int h, Align align = Align::None, Widget* parent = nullptr);
	~ListWidget() override = default;

	void onLogic() override;
	void onSelfRender(int renderX, int renderY) override;
	void onDestroy() override;

	void onMouseWheel(int delta) override;
	void onMousePressed(MouseEvent* ev) override;
	void onMouseMove(MouseEvent* ev) override;
	void onMouseReleased(MouseEvent* ev) override;

	void updateOffset();
	void updateMouseIndexByMousePos();
	int getMouseIndex(int mouseX, int mouseY);

	void addItem(ListWidgetItem* item);
	void removeItem(ListWidgetItem* item);
	void clearItem();

	void setClickedSlot(Object* _slotObject, ListWidgetSlot _slot);
	Object* slotObject = nullptr;
	ListWidgetSlot slot = nullptr;

	std::vector<ListWidgetItem*> vItems;

	int spacing = 4;
	int margin = 4;
	int btnHeight = 40;

	int mouseIndex = -1;
	bool isHolding = false;

	int focusIndex = -1;
	bool canBtnBeFocused = false;

	bool isContainsMouse = false;

	int yOffset = 0;
	int spd = 0;
	bool needUpdateOffset = false;
	bool needCheckMouse = false;
};