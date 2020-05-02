#ifndef _UTILITY_D3D9_H
#define _UTILITY_D3D9_H

#pragma region windows的头文件和库文件
//-------Windows头及库文件-------
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define MyMsgBox(str, title) MessageBox(nullptr, str.c_str(), title.c_str(), MB_OK)


inline RECT rect(int x, int y, int w, int h) {
    RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;
    return rect;
}

#pragma endregion


#pragma region d3d9的头文件和库文件
//-------D3D头及库文件-------
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")



//-------------------------
struct Vertex
{
    float x, y, z, rhw;
    DWORD color;
};

#define CHECK_HR(hr, ...) if(FAILED(hr))##__VA_ARGS__

//, 路径, 宽(来自图片D3DX_FROM_FILE), 高, 多级渐进纹理的等级, 图片的作用, 未知纹理格式, 受系统管理的存储空间, , , , 图片详细信息存储在这个结构体中, 调色板信息, 返回的纹理指针
#define myCreateTexture(g_pDevice, path, w, h, imageInfo, g_pTexture) \
    D3DXCreateTextureFromFileEx(\
        g_pDevice,\
        stringToWstring(path).c_str(), \
        w, h, \
        0, 0, \
        D3DFMT_UNKNOWN, \
        D3DPOOL_MANAGED, \
        D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL,\
        imageInfo, \
        nullptr, \
        g_pTexture\
    );

#define myCreateTextureSizeFromFile(g_pDevice, path, imageInfo, g_pTexture) \
            myCreateTexture(g_pDevice, path, D3DX_FROM_FILE, D3DX_FROM_FILE, imageInfo, g_pTexture)

#pragma endregion


#endif;