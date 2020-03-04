//-------Windows头及库文件-------
#ifndef WINDOWS_PLATFORM_
#define WINDOWS_PLATFORM_

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#endif

//-------D3D头及库文件-------
#ifndef D3D_USEFUL_H_
#define D3D_USEFUL_H_

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#endif

//-------SAFE_DELETE_----------
#ifndef SAFE_DELETE_T_
#define SAFE_DELETE_T_

template<typename T>inline void Safe_Delete(T*& p)
{
    if (p) { delete p; p = nullptr; }
}

template<typename T>inline void Safe_Release(T*& p)
{
    if (p) { p->Release(); p = nullptr; }
}
#endif

//------读取纹理-------
#ifndef READ_TEXTURE
#define READ_TEXTURE
#include <string>
LPCWSTR stringToLPCWSTR(std::string orig);
void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path, D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture);
#endif

//------得到时间(ms)------
#ifndef GET_TIME
#define GET_TIME
#include <time.h>
#include <sys/timeb.h>
#include <sstream>
long long getCurrentTime();
#endif