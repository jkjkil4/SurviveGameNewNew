#include "ListWidget.h"

using namespace My;
using namespace std;

ListWidget::ListWidget(int w, int h, Align align, Widget* parent) : Widget(w, h, align, parent)
{
    createRenderTarget();
    isMouseTracking = true;
}


void ListWidget::onLogic() {
    if (needUpdateOffset)
        updateOffset();

    if (isContainsMouse) {
        int localX = engine.mouseX - wndX;
        int localY = engine.mouseY - wndY;
        if (localX < 0 || localX > w || localY < 0 || localY > h || !isVisible()) {
            updateMouseIndexByMousePos();
            isContainsMouse = false;
        }
    }
}

void ListWidget::onSelfRender(int renderX, int renderY) {
    RECT rect;
    rect.left = renderX + margin;
    rect.right = renderX + w - margin;
    
    int startIndex = max((-yOffset - margin) / (btnHeight + spacing), 0);
    int endIndex = min((h - yOffset - margin) / (btnHeight + spacing) + 1, (int)vItems.size());

    engine.drawRestart();
    for (int i = startIndex; i < endIndex; i++) {
        rect.top = renderY + margin + i * (btnHeight + spacing) + yOffset;
        rect.bottom = rect.top + btnHeight;

        ListWidgetItem::ItemFlag flag = ListWidgetItem::ItemFlag::None;
        if (mouseIndex == i) {
            flag = isHolding
                ? ListWidgetItem::ItemFlag::MouseHolding
                : ListWidgetItem::ItemFlag::MouseAt;
        }

        vItems[i]->onPaint(rect, flag, canBtnBeFocused && focusIndex == i);
    }
}

void ListWidget::onDestroy() {
    clearItem();
}


void ListWidget::onMouseWheel(int delta) {
    int num = delta / 10;
    if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
        spd = 0;
    spd += num;
    if (abs(spd) > 16)
        spd > 0 ? spd = 16 : spd = -16;

    needUpdateOffset = true;
}

void ListWidget::onMousePressed(MouseEvent* ev) {
    if (ev->button == Mouse::Left) {
        isHolding = true;
        updateMouseIndexByMousePos();

        if (canBtnBeFocused && mouseIndex != -1) {
            focusIndex = mouseIndex;
        }
        if (mouseIndex != -1 && slotObject) {
            (slotObject->*slot)(vItems[mouseIndex]);
        }
    }
}

void ListWidget::onMouseMove(MouseEvent* ev) {
    isContainsMouse = true;
    if (!(ev->button & Mouse::Left)) {
        needCheckMouse = true;
        updateMouseIndexByMousePos();
    }
}

void ListWidget::onMouseReleased(MouseEvent* ev) {
    if (ev->button == Mouse::Left) {
        isHolding = false;

        updateMouseIndexByMousePos();
    }
}


void ListWidget::updateOffset() {
    if (spd != 0) {
        //sumSpdToOffset
        yOffset += spd;
        if (spd > 0) {
            spd -= 1;
            if (spd < 0)
                spd = 0;
        }
        else if (spd < 0) {
            spd += 1;
            if (spd > 0)
                spd = 0;
        }
    }

    bool isMoving = false;
    int min = min(h - ((btnHeight + spacing) * (int)vItems.size() + 2 * margin - spacing), 0);
    if (yOffset > 0 || yOffset < min) {
        //isMoving = limitOffset(min);
        //limitOffset
        if (yOffset > 0) {
            int limitSpd = 2 + yOffset / 4;
            yOffset -= limitSpd;
            if (yOffset < 0)
                yOffset = 0;
            isMoving = true;
        }
        else if (yOffset < min) {
            int limitSpd = 2 + (min - yOffset) / 4;
            yOffset += limitSpd;
            if (yOffset > min)
                yOffset = min;
            isMoving = true;
        }
        else isMoving = false;
    }

    if(!isHolding)
        updateMouseIndexByMousePos();

    if (spd == 0 && !isMoving)
        needUpdateOffset = false;
}

void ListWidget::updateMouseIndexByMousePos() {
    mouseIndex = getMouseIndex(engine.mouseX - wndX, engine.mouseY - wndY);
}

int ListWidget::getMouseIndex(int mouseX, int mouseY) {
    if (mouseX < margin || mouseX > w - margin || mouseY < 0 || mouseY > h)
        return -1;
    int localY = (mouseY - yOffset - margin) % (btnHeight + spacing);
    if (localY > btnHeight)
        return -1;
    int index = (mouseY - yOffset - margin) / (btnHeight + spacing);
    if (index < 0 || index >= (int)vItems.size())
        return -1;

    return index;
}


void ListWidget::addItem(ListWidgetItem* item) {
	vItems.push_back(item);
}

void ListWidget::removeItem(ListWidgetItem* item) {
	for (auto iter = vItems.begin(); iter < vItems.end(); iter++) {
		if (*iter == item) {
			delete item;
			vItems.erase(iter);
			break;
		}
	}
    mouseIndex = -1;
    focusIndex = -1;
    needUpdateOffset = true;
}

void ListWidget::clearItem() {
	for (auto item : vItems) {
		delete item;
	}
	vItems.clear();
    mouseIndex = -1;
    focusIndex = -1;
    needUpdateOffset = true;
}


void ListWidget::setClickedSlot(Object* _slotObject, ListWidgetSlot _slot) {
    slotObject = _slotObject;
    slot = _slot;
}