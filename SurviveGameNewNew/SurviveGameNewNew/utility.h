#ifndef _UTILITY_H
#define _UTILITY_H

//-------Windows头及库文件-------
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//-------D3D头及库文件-------
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

//-------SAFE_DELETE_----------
template<typename T>inline void safeDelete(T*& p) {
    if (p) { delete p; p = nullptr; }
}
template<typename T>inline void safeRelease(T*& p) {
    if (p) { p->Release(); p = nullptr; }
}

//------D3D相关操作----
#include <string>
void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path, UINT w, UINT h, D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture);
void mySetScale(LPD3DXSPRITE pSpr, float scalePosX, float scalePosY, float xScale, float yScale, 
    float rotPosX = 0, float rotPosY = 0, float rot = 0);

//------类型转换-------
std::wstring stringToWstring(std::string orig);

//------多线程---------
#include <thread>

//------math----------
#include <cmath>
#define PI acos(-1)

//------文件操作-------
#include <vector>
#include <fstream>
void getFiles(std::string path, std::string exd, std::vector<std::wstring>* files);

//------别的东西-------
#define MyMsgBox(str) MessageBox(nullptr, stringToWstring(str).c_str(), TEXT("1"), MB_OK)
#define cDebug(str) OutputDebugString( stringToWstring(str).c_str() )
inline RECT rect(int x, int y, int w, int h) {
    RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;
    return rect;
}

//------计算-------
template<typename T>inline T myMax(T a, T b) {
    return a > b ? a : b;
}
template<typename T>inline T myMin(T a, T b) {
    return a > b ? b : a;
}
template<typename T>inline T myBound(T min, T value, T max) {
    return myMin(myMax(value, min), max);
}

#endif //_UTILITY_H