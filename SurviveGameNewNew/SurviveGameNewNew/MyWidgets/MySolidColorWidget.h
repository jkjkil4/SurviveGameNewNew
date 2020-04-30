#ifndef _MYSOLIDCOLORWIDGET_H
#define _MYSOLIDCOLORWIDGET_H	

#include "MyWidget.h"

class MySolidColorWidget : public MyWidget
{
public:
	explicit MySolidColorWidget(MyEngine* e, int w, int h, MyWidget* parent = nullptr);
	~MySolidColorWidget() override = default;

	inline void _onRender(LPD3DXSPRITE g_pSprite, int targetX, int targetY);

	D3DCOLOR color = 0xffffffff;
};

#endif