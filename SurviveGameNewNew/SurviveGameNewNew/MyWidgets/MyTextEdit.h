#ifndef _MYTEXTEDIT_H
#define _MYTEXTEDIT_H

#include "MyWidget.h"

class MyTextEdit : public MyWidget
{
public:
	explicit MyTextEdit(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, 
		LPD3DXFONT g_pFont, MyWidget* parent = nullptr);

	inline void _onRender(LPD3DXSPRITE g_pSprite) override;

	inline void _mouseEvent(MyMouseEvent ev) override;

	inline void _keyboardEvent(std::wstring wstr) override;

	LPD3DXFONT g_pFont = nullptr;

	std::wstring text = TEXT("");
};

#endif //_MYTEXTEDIT_H