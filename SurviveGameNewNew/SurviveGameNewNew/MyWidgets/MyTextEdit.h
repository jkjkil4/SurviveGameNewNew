#ifndef _MYTEXTEDIT_H
#define _MYTEXTEDIT_H

#include "MyWidget.h"

class MyTextEdit : public MyWidget
{
public:
	explicit MyTextEdit(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, 
		LPD3DXFONT g_pFont, MyWidget** focusWidget, MyWidget* parent = nullptr);

	inline void _onRender(LPD3DXSPRITE g_pSprite) override;

	inline void _mouseEvent(MyMouseEvent) override;

	inline void _keyboardEvent(std::wstring wstr) override;

	LPD3DXFONT g_pFont = nullptr;

	std::wstring text = TEXT("");

	bool focusVisible = true;
	int focusTimer = 0;
};

#endif //_MYTEXTEDIT_H