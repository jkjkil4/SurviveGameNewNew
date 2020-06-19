#include "utility.h"

using namespace std;

inline void My::createTextureFromFile(LPDevice g_pDevice, wstring& path, UINT w, UINT h, ImageInfo* imageInfo, LPTexture* g_pTexture) {
    D3DXCreateTextureFromFileEx(
        g_pDevice,
        path.c_str(),
        w, h,
        0, 0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL,
        imageInfo,
        nullptr,
        g_pTexture
        );
}
inline void My::createTextureSizeFromFile(LPDevice g_pDevice, wstring& path, ImageInfo* imageInfo, LPTexture* g_pTexture) {
    createTextureFromFile(g_pDevice, path, D3DX_FROM_FILE, D3DX_FROM_FILE, imageInfo, g_pTexture);
}

void My::setSpriteScale(LPSprite pSpr, float scalePosX, float scalePosY, float xScale, float yScale,
	float rotPosX, float rotPosY, float rot) {
	D3DXMATRIX g_scale;
	D3DXMatrixTransformation2D(
		&g_scale,		//���صľ���
		&D3DXVECTOR2(scalePosX, scalePosY),		//���ŵ�����
		0.0f,			//Ӱ�����ŵ�����
		&D3DXVECTOR2(xScale, yScale),	//����
		&D3DXVECTOR2(rotPosX, rotPosY),	//��ת����
		rot,			//��ת����
		nullptr		//ƽ����
		);
	pSpr->SetTransform(&g_scale);
	D3DXMatrixIdentity(&g_scale);
}