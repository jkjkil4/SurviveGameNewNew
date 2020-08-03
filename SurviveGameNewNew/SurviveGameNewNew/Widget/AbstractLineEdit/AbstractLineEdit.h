#pragma once

#include "../Widget.h"

namespace My {
	//输入框的抽象类，继承该类重写onSelfRender来进行绘制
	//调用该类的renderText来绘制文字
	class AbstractLineEdit;
}

//#define DEBUG_LINEEDIT

class My::AbstractLineEdit : public Widget
{
public:
	struct BoxOffset {
		int xOffset = 0, yOffset = 0, wOffset = 0, hOffset = 0;
	}boxOffset;

	AbstractLineEdit(LPFont font, TextAlign textAlign, int w, int h, Align align = Align::None, Widget* parent = nullptr);
	~AbstractLineEdit() override = default;

	void onLogic() override;
	
	void onMousePressed(MouseEvent* ev) override;
	void onMouseMove(MouseEvent* ev) override;

	void updateOffsetByIndex(int index);

	int getTextWidth();
	int getCursorIndex(int mouseX);
	int getIndexX(int index);

	void drawText(int renderX, int renderY);

	LPFont font;
	TextAlign textAlign;
	std::wstring text;
	D3DCOLOR textColor = 0xff000000;
	int margin = 2;

	//当textAlign为Scroll时用来定位字符位置的东西
	int strPos = 0;	
	int charOffset = 0;

	//定位光标位置的东西
	int cursorBegin = 0;
	int cursorEnd = 0;

	//用来控制光标闪烁的东西
	SC int cursorShowTimes = 30;
	int cursorShowCountTimes = 0;
	bool isCursorShow = true;
};