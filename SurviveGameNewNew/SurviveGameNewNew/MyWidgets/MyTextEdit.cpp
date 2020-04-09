#include "MyTextEdit.h"

using namespace std;

MyTextEdit::MyTextEdit(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, 
	LPD3DXFONT g_pFont, MyWidget* parent)
	: MyWidget(e, g_pTexture, pTextureInfo, parent)
{
	this->g_pFont = g_pFont;
}

inline void MyTextEdit::_onRender(LPD3DXSPRITE g_pSprite) {
	g_pFont->DrawText(g_pSprite, text.c_str(), -1, &rect(wndX, wndY, w, h), DT_CENTER | DT_VCENTER, 0xffffffff);
}

inline void MyTextEdit::_mouseEvent(MyMouseEvent ev) {
	
}

inline void MyTextEdit::_keyboardEvent(wstring wstr) {
	text += wstr;
}
