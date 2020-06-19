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
		&g_scale,		//返回的矩阵
		&D3DXVECTOR2(scalePosX, scalePosY),		//缩放的中心
		0.0f,			//影响缩放的因素
		&D3DXVECTOR2(xScale, yScale),	//缩放
		&D3DXVECTOR2(rotPosX, rotPosY),	//旋转中心
		rot,			//旋转弧度
		nullptr		//平移量
		);
	pSpr->SetTransform(&g_scale);
	D3DXMatrixIdentity(&g_scale);
}