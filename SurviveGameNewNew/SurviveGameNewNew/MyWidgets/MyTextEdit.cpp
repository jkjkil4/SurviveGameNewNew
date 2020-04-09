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
	wstring result = TEXT("");
	for (int i = 0; i < (int)wstr.length(); i++) {
		WCHAR ch = wstr[i];
		if (ch < 0x0021) {	//³ýÈ¥¿ØÖÆ×Ö·û
			if (ch == 0x0008) {	//ÍË¸ñ¼ü
				if (i == 0) {
					if (text.length() != 0)
						text.pop_back();
				}
				else {
					if (result.length() != 0)
						result.pop_back();
				}
			}
			continue;
		}
		result += ch;
	}
	text += result;
}
