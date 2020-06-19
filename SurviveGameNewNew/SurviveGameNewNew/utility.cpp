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
    My::createTextureFromFile(g_pDevice, path, D3DX_FROM_FILE, D3DX_FROM_FILE, imageInfo, g_pTexture);
}