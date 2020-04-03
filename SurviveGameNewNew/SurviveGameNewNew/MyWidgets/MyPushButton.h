#ifndef _MYPUSHBUTTON_H
#define _MYPUSHBUTTON_H

#include "MyWidget.h"

class MyPushButton : public MyWidget
{
public:
	explicit MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget* parent = nullptr);
	~MyPushButton() override;

	void mouseEvent(int type, int mouse, int x, int y) override;
};

#endif //_MYPUSHBUTTON_H

