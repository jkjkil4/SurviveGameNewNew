#include "MyPushButton.h"

using namespace std;

MyPushButton::MyPushButton(MyEngine* e, LPDIRECT3DTEXTURE9 g_pTexture, D3DXIMAGE_INFO* pTextureInfo, MyWidget* parent) 
	: MyWidget(e, g_pTexture, pTextureInfo, parent) {}

MyPushButton::~MyPushButton(){}

void MyPushButton::mouseEvent(int type, int mouse, int x, int y) {
	cDebug("状态: " + to_string(type) + "\t按键: " + to_string(mouse) 
		+ "\t局部坐标: " + to_string(x) + " , " + to_string(y) + "\n");
}

