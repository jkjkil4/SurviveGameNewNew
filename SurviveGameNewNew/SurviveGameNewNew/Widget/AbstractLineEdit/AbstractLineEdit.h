#pragma once

#include "../Widget.h"

namespace My {
	//�����ĳ����࣬�̳и�����дonSelfRender�����л���
	//���ø����drawText����������
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

	void onKeyPressed(KeyEvent* ev) override;

	void setCursorEnable();
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

	//��textAlignΪScrollʱ������λ�ַ�λ�õĶ���
	int strPos = 0;	
	int charOffset = 0;

	//��λ���λ�õĶ���
	int cursorBegin = 0;
	int cursorEnd = 0;

	//�������ƹ����˸�Ķ���
	SC int cursorShowTimes = 30;
	int cursorShowCountTimes = 0;
	bool isCursorShow = true;
};