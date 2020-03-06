//-------Windows头及库文件-------
#ifndef WINDOWS_PLATFORM_
#define WINDOWS_PLATFORM_

#define WIN32_LEAN_AND_MEAN
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

template<typename T>inline void Safe_Delete(T*& p){
    if (p) { delete p; p = nullptr; }
}

template<typename T>inline void Safe_Release(T*& p){
    if (p) { p->Release(); p = nullptr; }
}
#endif

//------读取纹理-------
#ifndef READ_TEXTURE_
#define READ_TEXTURE_
#include <string>
void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path, D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture);
#endif

//------类型转换-------
#ifndef TYPE_TRANSLATE_
#define TYPE_TRANSLATE_
#define cDebug(str) OutputDebugString( stringToWstring(str).c_str() )
std::wstring stringToWstring(std::string orig);
#endif

//------多线程---------
#ifndef PTHREAD_
#define PTHREAD_
#include <thread>
#endif

//------math----------
#ifndef MATH_
#include <cmath>
#define PI acos(-1)
#endif