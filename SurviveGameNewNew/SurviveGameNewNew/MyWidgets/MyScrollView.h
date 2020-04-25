#ifndef _MYSCROLLVIEW_H
#define _MYSCROLLVIEW_H

#include "MyWidget.h"

class MyScrollView : public MyWidget
{
public:
	explicit MyScrollView(MyEngine* e, int w, int h, MyWidget* parent = nullptr);
	~MyScrollView() override = default;

	void updateChildPos();

	void sumSpdToOffset();

	void clear();

	inline void _onRender(LPD3DXSPRITE, int, int) override;

	inline void _wheelEvent(int, int, int delta) override;

	int offset = 0;
	int spd = 0;

	int childH = 20;

	int borderWidth = 4;
};

#endif