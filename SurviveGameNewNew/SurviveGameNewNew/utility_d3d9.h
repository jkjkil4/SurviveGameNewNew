#ifndef _UTILITY_D3D9_H
#define _UTILITY_D3D9_H

#pragma region windows��ͷ�ļ��Ϳ��ļ�
//-------Windowsͷ�����ļ�-------
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


#pragma region d3d9��ͷ�ļ��Ϳ��ļ�
//-------D3Dͷ�����ļ�-------
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

//, ·��, ��(����ͼƬD3DX_FROM_FILE), ��, �༶��������ĵȼ�, ͼƬ������, δ֪�����ʽ, ��ϵͳ����Ĵ洢�ռ�, , , , ͼƬ��ϸ��Ϣ�洢������ṹ����, ��ɫ����Ϣ, ���ص�����ָ��
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