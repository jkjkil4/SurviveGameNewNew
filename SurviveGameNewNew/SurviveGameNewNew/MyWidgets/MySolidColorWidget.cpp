#include "MySolidColorWidget.h"

MySolidColorWidget::MySolidColorWidget(MyEngine* e, int w, int h, MyWidget* parent)
	: MyWidget(e, w, h, nullptr, parent) {}

inline void MySolidColorWidget::_onRender(LPD3DXSPRITE g_pSprite, int targetX, int targetY) {
	e->drawRestart();
	e->drawRect(targetX, targetY, w, h, color, color, color, color);
}