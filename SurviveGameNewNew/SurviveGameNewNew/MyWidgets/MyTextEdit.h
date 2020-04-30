#ifndef _MYTEXTEDIT_H
#define _MYTEXTEDIT_H

#include "MyWidget.h"

class MyTextEdit : public MyWidget
{
public:
	explicit MyTextEdit(MyEngine* e, int w, int h, LPD3DXFONT g_pFont, MyWidget** focusWidget, MyWidget* parent = nullptr);
	~MyTextEdit() override = default;

	inline void resetFocusTimer();
	void clear();

	inline void _onRender(LPD3DXSPRITE g_pSprite, int renderX, int renderY) override;

	inline void _mouseEvent(MyMouseEvent) override;
	inline void _charEvent(std::wstring wstr) override;
	inline void _keyboardEvent(int key) override;

	LPD3DXFONT g_pFont = nullptr;

	D3DCOLOR textColor = 0xffffffff;
	D3DCOLOR bgColor = 0xff000000;
	D3DCOLOR bdColor = 0xffcccccc;

	std::wstring text = TEXT("");
	MyStrExpr expr;
	int index = 0;
	int maxLength = -1;

	bool focusVisible = true;
	int focusTimer = 0;
};

#endif //_MYTEXTEDIT_H